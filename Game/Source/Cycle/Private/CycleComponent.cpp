// Fill out your copyright notice in the Description page of Project Settings.


#include "CycleComponent.h"

#include "CycleSettings.h"

DEFINE_LOG_CATEGORY(LogCycle);

UCycleComponent::UCycleComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Settings = GetDefault<UCycleSettings>();
}

void UCycleComponent::Start()
{
	if (!ensure(!CurrentCycleDefinition.IsRunning()))
	{
		return;
	}

	if (CurrentCycleDefinition.CycleIndex == -1)
	{
		if (!ensure(!Settings->CycleSequence.IsEmpty()))
		{
			return;
		}
		
		CurrentCycleDefinition.CycleIndex = 0;
	}

	UE_LOG(LogCycle, Log, TEXT("Starting Cycle Component"));
	CurrentCycleDefinition.StartTime = GetWorld()->GetTimeSeconds();
	
	CurrentCycleDefinition.Event = TAG_Cycle_Event_Start;
	CurrentCycleDefinition.EventTags = {};
	CurrentCycleDefinition.EventTags.AddTag(Settings->CycleSequence[CurrentCycleDefinition.CycleIndex]);
	CurrentCycleDefinition.EventTags.AddTag(TAG_Cycle_State_Running); 
	
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);}

void UCycleComponent::Stop()
{
	if (!ensure(CurrentCycleDefinition.IsRunning()))
	{
		return;
	}

	UE_LOG(LogCycle, Log, TEXT("Stopping Cycle Component"));
	CurrentCycleDefinition.Event = TAG_Cycle_Event_Stop;
	CurrentCycleDefinition.EventTags.RemoveTag(TAG_Cycle_State_Running);
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}

void UCycleComponent::Reset()
{
	UE_LOG(LogCycle, Log, TEXT("Reset Cycle Component"));
	CurrentCycleDefinition = {};
	CurrentCycleDefinition.Event = TAG_Cycle_Event_Reset;
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}

void UCycleComponent::SetMultiplier(const float Multiplier)
{
	if (!ensure(CurrentCycleDefinition.IsRunning()))
	{
		return;
	}

	if (!ensureAlways(Multiplier > 0.f))
	{
		return;
	}

	UE_LOG(LogCycle, Log, TEXT("SetMultiplier Cycle Component %f"), Multiplier);
	CurrentCycleDefinition.Multiplier = Multiplier;
	CurrentCycleDefinition.Event = TAG_Cycle_Event_Multiplier;
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}

void UCycleComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentCycleDefinition.IsRunning() && !CurrentCycleDefinition.IsCompleted())
	{
		CurrentCycleDefinition.CurrentTime += DeltaTime * CurrentCycleDefinition.Multiplier;

		if (CurrentCycleDefinition.CurrentTime >= Settings->SegmentLength)
		{
			SetNextCycle();
		}
	}
}

void UCycleComponent::SetNextCycle()
{
	CurrentCycleDefinition.StartTime = GetWorld()->GetTimeSeconds();

	// Substract the Segment length from the current time so it's carry over to next segment
	CurrentCycleDefinition.CurrentTime -= Settings->SegmentLength;
	CurrentCycleDefinition.CurrentTime = FMath::Max(CurrentCycleDefinition.CurrentTime, 0.f);

	// Increment to next cycle
	CurrentCycleDefinition.CycleIndex += 1;

	CurrentCycleDefinition.Event = TAG_Cycle_Event_SetNextSegment;

	CurrentCycleDefinition.EventTags = {};

	// If index is invalid means we have reached the end of the cycle
	const bool bIsInNewSegment = Settings->CycleSequence.IsValidIndex(CurrentCycleDefinition.CycleIndex);

	if (bIsInNewSegment)
	{
		CurrentCycleDefinition.EventTags.AddTag(Settings->CycleSequence[CurrentCycleDefinition.CycleIndex]);
	}

	// If we reach the end of the cycle it's over so we set it to complete
	CurrentCycleDefinition.EventTags.AddTag(bIsInNewSegment ? TAG_Cycle_State_Running : TAG_Cycle_State_Completed); 
	
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}
