// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolSubsystem.h"

#include "GameplayTagContainer.h"
#include "PoolActorInterface.h"
#include "PoolDataTypes.h"
#include "PoolSettings.h"
#include "Engine/AssetManager.h"

DEFINE_LOG_CATEGORY(LogPoolSubsystem);


void UPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	PoolSettings = GetDefault<UPoolSettings>();
}

void UPoolSubsystem::SpawnActor(const FGameplayTag& Tag, const FActorInitializationParams& Params)
{
	if (FActorPool* Pool = ActorPoolMap.Find(Tag); Pool)
	{
		OnActorLoaded(Pool, Params);
	}
	else if (const TSoftObjectPtr<UPoolActorData>* SoftPtr = PoolSettings->NameToPoolData.Find(Tag); SoftPtr)
	{
		FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
		auto Delegate = FStreamableDelegate::CreateUObject(this, &UPoolSubsystem::OnDataLoaded, Tag, Params);
		StreamableManager.RequestAsyncLoad(SoftPtr->ToSoftObjectPath(), Delegate);
	}
	else
	{
		UE_LOG(LogPoolSubsystem, Error, TEXT("Failed to spawn actor %s"), *Tag.ToString());
	}
}

void UPoolSubsystem::ReturnActor(AActor* Actor)
{
	if (!ensureAlways(IsValid(Actor)))
	{
		return;
	}
	
	if (Actor->Implements<UPoolActorInterface>())
	{
		IPoolActorInterface* PoolActorInterface = CastChecked<IPoolActorInterface>(Actor);
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
	if (!ensureAlways(Pool))
	{
		return;
	}
	
	if (Pool->PooledActors.IsEmpty())
	{
		FActorSpawnParameters SpawnParams;
		AActor* SpawnedActor = GetWorld()->SpawnActor(Pool->PoolData->RootActor);
		Pool->PooledActors.Add(SpawnedActor);
	}

	const int32 IndexToGet = Pool->PooledActors.Num() - 1;
	AActor* Actor = Pool->PooledActors[IndexToGet];
	Pool->PooledActors.RemoveAt(IndexToGet);

	Params.InitializeActor.ExecuteIfBound(Actor);
	Params.PlaceActor.ExecuteIfBound(Actor);

	if (ensureAlways(Actor->Implements<UPoolActorInterface>()))
	{
		IPoolActorInterface* PoolActorInterface = CastChecked<IPoolActorInterface>(Actor);
		Pool->ActorsGenerated += 1;
		PoolActorInterface->ActorPool = MakeShared<FActorPool>(*Pool);
		PoolActorInterface->Activate();
	}
}

void UPoolSubsystem::OnDataLoaded(const FGameplayTag Tag, FActorInitializationParams Params)
{
	const TSoftObjectPtr<UPoolActorData>* SoftPtr = PoolSettings->NameToPoolData.Find(Tag);
	
	FActorPool NewPool;
	NewPool.PoolData = SoftPtr->Get();
	FActorPool& Pool = ActorPoolMap.Add(Tag, NewPool);
	OnActorLoaded(&Pool, Params);
}
