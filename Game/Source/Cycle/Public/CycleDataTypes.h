// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

#include "CycleDataTypes.generated.h"

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Event_Start);

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Event_Stop);

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Event_Reset);

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Event_SetNextSegment);

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Event_Multiplier);


CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_State_Running);

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_State_Completed);


CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Parameter_CycleIndex);

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Parameter_StartTime);

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Parameter_CurrentTime);

CYCLE_API
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Cycle_Parameter_Multiplier);

USTRUCT(BlueprintType)
struct CYCLE_API FCycleDefinition
{
	GENERATED_BODY()

	int32 CycleIndex = -1;
	float StartTime = -1.f;
	float CurrentTime = 0.f;
	float Multiplier = 1.f;

	FGameplayTag Event;
	FGameplayTagContainer EventTags;

	bool IsRunning() const
	{
		return EventTags.HasTagExact(TAG_Cycle_State_Running);
	}

	bool IsCompleted() const
	{
		return EventTags.HasTagExact(TAG_Cycle_State_Completed);
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("CycleDefinition: %d, %f, %f, %f"), CycleIndex, StartTime, CurrentTime, Multiplier);
	}
};