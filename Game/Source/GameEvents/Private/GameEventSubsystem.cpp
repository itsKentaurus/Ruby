// Fill out your copyright notice in the Description page of Project Settings.

#include "GameEventSubsystem.h"

#include "GameEventDataTypes.h"

DEFINE_LOG_CATEGORY(LogGameEvent);

void UGameEventSubsystem::TriggerEvent(const UObject* WorldContextObject, const FGameEventData& EventData)
{
	if (auto* Subsystem = GetSubsystem(WorldContextObject); IsValid(Subsystem))
	{
		Subsystem->OnEventTriggered(EventData);
	}
}

void UGameEventSubsystem::OnEventTriggered(const FGameEventData& EventData)
{
	UE_LOG(LogGameEvent, Verbose, TEXT("EventData: %s"), *EventData.EventTag.ToString());
	UE_LOG(LogGameEvent, Verbose, TEXT("Count: %d"), EventData.Count);
	for (int i = 0; i < EventData.TagParameters.Num(); ++i)
	{
		UE_LOG(LogGameEvent, Verbose, TEXT("TagParameter(%d): %s"), i, *EventData.TagParameters.GetByIndex(i).ToString());	
	}

	for (const TPair<FGameplayTag, double>& Tuple : EventData.Parameters) 
	{
		UE_LOG(LogGameEvent, Verbose, TEXT("Parameter(%s): %f"), *Tuple.Key.ToString(), Tuple.Value);	
	}
	
	OnTriggerEvents.ExecuteIfBound(EventData);
}

UGameEventSubsystem* UGameEventSubsystem::GetSubsystem(const UObject* Object)
{
	if (!IsValid(Object))
	{
		return nullptr;
	}

	const UWorld* World = Object->GetWorld();
	const UGameInstance* GameInstance = IsValid(World) ? World->GetGameInstance() : nullptr;
	return IsValid(GameInstance) ? GameInstance->GetSubsystem<UGameEventSubsystem>() : nullptr;
}
