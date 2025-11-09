// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "PoolDataTypes.h"
#include "Subsystems/WorldSubsystem.h"
#include "PoolSubsystem.generated.h"

struct FActorInitializationParams;
class UPoolSettings;

DECLARE_LOG_CATEGORY_EXTERN(LogPoolSubsystem, Log, All);

/**
 * 
 */
UCLASS()
class POOL_API UPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SpawnActor(const FGameplayTag& Tag, const FActorInitializationParams& Params);
	static void ReturnActor(AActor* Actor);

private:
	UPROPERTY(Transient)
	TObjectPtr<const UPoolSettings> PoolSettings = nullptr;

	UPROPERTY(Transient)
	TMap<FGameplayTag, FActorPool> ActorPoolMap;

	TMap<FGameplayTag, int32> ActorsToSpawn;

	void OnActorLoaded(FActorPool* Pool, const FActorInitializationParams& Params) const;
	void OnDataLoaded(const FGameplayTag Tag, FActorInitializationParams Params);
};
