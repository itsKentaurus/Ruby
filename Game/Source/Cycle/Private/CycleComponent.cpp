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
	if (!ensure(!CurrentCycleDefinition.bIsRunning))
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
	CurrentCycleDefinition.bIsRunning = true;
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}

void UCycleComponent::Stop()
{
	if (!ensure(CurrentCycleDefinition.bIsRunning))
	{
		return;
	}

	UE_LOG(LogCycle, Log, TEXT("Stopping Cycle Component"));
	CurrentCycleDefinition.bIsRunning = false;
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}

void UCycleComponent::Reset()
{
	UE_LOG(LogCycle, Log, TEXT("Reset Cycle Component"));
	CurrentCycleDefinition = {};
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}

void UCycleComponent::SetMultiplier(const float Multiplier)
{
	if (!ensure(CurrentCycleDefinition.bIsRunning))
	{
		return;
	}

	if (!ensureAlways(Multiplier > 0.f))
	{
		return;
	}

	UE_LOG(LogCycle, Log, TEXT("SetMultiplier Cycle Component %f"), Multiplier);
	CurrentCycleDefinition.Multiplier = Multiplier;
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}

void UCycleComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentCycleDefinition.bIsRunning && !CurrentCycleDefinition.bIsComplete)
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

	// If we reach the end of the cycle it's over so we set it to complete
	CurrentCycleDefinition.bIsRunning = Settings->CycleSequence.IsValidIndex(CurrentCycleDefinition.CycleIndex);
	CurrentCycleDefinition.bIsComplete = !CurrentCycleDefinition.bIsRunning;
	
	CycleUpdated.ExecuteIfBound(CurrentCycleDefinition);
}
