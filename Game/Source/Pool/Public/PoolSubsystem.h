// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PoolDataTypes.h"
#include "Subsystems/WorldSubsystem.h"
#include "PoolSubsystem.generated.h"

struct FActorInitializationParams;
class UPoolSettings;

/**
 * 
 */
UCLASS()
class POOL_API UPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SpawnActor(const FName& Name, const FActorInitializationParams& Params);
	static void ReturnActor(AActor* Actor);

private:
	UPROPERTY(Transient)
	TObjectPtr<const UPoolSettings> PoolSettings = nullptr;

	UPROPERTY(Transient)
	TMap<FName, FActorPool> ActorPoolMap;

	TMap<FName, int32> ActorsToSpawn;

	void OnActorLoaded(FActorPool* Pool, const FActorInitializationParams& Params) const;
	void OnDataLoaded(const FName PoolName, FActorInitializationParams Params);
};
