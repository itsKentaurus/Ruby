// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolSubsystem.h"

#include "PoolActorInterface.h"
#include "PoolDataTypes.h"
#include "PoolSettings.h"
#include "Engine/AssetManager.h"

void UPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	PoolSettings = GetDefault<UPoolSettings>();
}

void UPoolSubsystem::SpawnActor(const FName& Name, const FActorInitializationParams& Params)
{
	FActorPool* Pool = ActorPoolMap.Find(Name);
	if (!Pool)
	{
		auto* SoftPtr = PoolSettings->NameToPoolData.Find(Name);
		
		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		auto Delegate = FStreamableDelegate::CreateUObject(this, &UPoolSubsystem::OnDataLoaded, Name, Params);
		StreamableManager.RequestAsyncLoad(SoftPtr->ToSoftObjectPath(), Delegate);
	}
	else
	{
		OnActorLoaded(Pool, Params);
	}
}

void UPoolSubsystem::ReturnActor(AActor* Actor)
{
	if (Actor->Implements<UPoolActorInterface>())
	{
		auto* PoolActorInterface = CastChecked<IPoolActorInterface>(Actor);
		PoolActorInterface->Deactivate();
		PoolActorInterface->ActorPool->Return(Actor);
	}
	else
	{
		Actor->LifeSpanExpired();
	}
}

void UPoolSubsystem::OnActorLoaded(FActorPool* Pool, const FActorInitializationParams& Params) const
{
	if (Pool->PooledActors.IsEmpty())
	{
		FActorSpawnParameters SpawnParams;
		auto* SpawnedActor = GetWorld()->SpawnActor(Pool->PoolData->RootActor);
		Pool->PooledActors.Add(SpawnedActor);
	}

	const int32 IndexToGet = Pool->PooledActors.Num() - 1;
	AActor* Actor = Pool->PooledActors[IndexToGet];
	Pool->PooledActors.RemoveAt(IndexToGet);

	Params.InitializeActor.ExecuteIfBound(Actor);
	Params.PlaceActor.ExecuteIfBound(Actor);

	if (Actor->Implements<UPoolActorInterface>())
	{
		auto* PoolActorInterface = CastChecked<IPoolActorInterface>(Actor);
		PoolActorInterface->ActorPool = MakeShared<FActorPool>(*Pool);
		PoolActorInterface->Activate();
	}
}

void UPoolSubsystem::OnDataLoaded(const FName PoolName, FActorInitializationParams Params)
{
	auto* SoftPtr = PoolSettings->NameToPoolData.Find(PoolName);
	
	FActorPool NewPool;
	NewPool.PoolData = SoftPtr->Get();
	auto& Pool = ActorPoolMap.Add(PoolName, NewPool);
	OnActorLoaded(&Pool, Params);
}
