// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "GameEventDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FGameEventData
{
	GENERATED_BODY()

	// Event called by the player
	// E.g., Unlock, Press, Etc...
	UPROPERTY(EditAnywhere, meta=(Categories="Event"))
	FGameplayTag EventTag;

	// The number of times that the event should be counted
	// E.g., Collect 100 Gold. Count will be 100, otherwise count will default to 1
	UPROPERTY(EditAnywhere)
	int32 Count = 1;

	// These are all items that have been used for this event
	// E.g., Difficulty, Characters, Weapons, Triggers, Etc...
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer TagParameters;
	
	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, double> Parameters;
	
	template<typename ValueType>
	ValueType GetValue(const FGameplayTag& Tag, ValueType DefaultValue);
};

template <typename ValueType>
ValueType FGameEventData::GetValue(const FGameplayTag& Tag, ValueType DefaultValue)
{
	if (!Parameters.Contains(Tag))
	{
		return DefaultValue;
	}
	
	return static_cast<ValueType>(Parameters[Tag]);
}
