// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PoolDataTypes.generated.h"

DECLARE_DELEGATE_OneParam(FPoolActorUpdate, AActor* Actor);

USTRUCT()
struct FActorInitializationParams
{
	GENERATED_BODY()

	FPoolActorUpdate InitializeActor;
	FPoolActorUpdate PlaceActor;
};

UCLASS()
class UPoolActorData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> RootActor = nullptr;

	UPROPERTY(EditAnywhere)
	int32 MaxPoolSize = 5;
};

USTRUCT()
struct FActorPool
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TArray<TObjectPtr<AActor>>PooledActors;

	UPROPERTY(Transient)
	TObjectPtr<UPoolActorData> PoolData = nullptr;

	int32 ActorCount = 0;

	void Return(AActor* Actor)
	{
		ActorCount -= 1;
		if (PooledActors.Num() < PoolData->MaxPoolSize)
		{
			Actor->SetActorLocation(FVector(10000.f, 10000.f, 10000.f), false, nullptr, ETeleportType::ResetPhysics);
			PooledActors.Add(Actor);
		}
		else
		{
			Actor->LifeSpanExpired();
		}
	}
};