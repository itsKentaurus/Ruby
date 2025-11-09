// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "PoolSettings.generated.h"

class UPoolActorData;

/**
 * 
 */
UCLASS(config = Game, DefaultConfig, meta = (DisplayName = "Pool Settings"))
class POOL_API UPoolSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Config, meta=(Categories="Pool.Actor"))
	TMap<FGameplayTag, TSoftObjectPtr<UPoolActorData>> NameToPoolData;
};
