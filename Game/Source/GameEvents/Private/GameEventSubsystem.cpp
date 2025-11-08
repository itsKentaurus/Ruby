// Fill out your copyright notice in the Description page of Project Settings.

#include "GameEventSubsystem.h"

void UGameEventSubsystem::TriggerEvent(const UObject* WorldContextObject, const FGameEventData& EventData)
{
	if (auto* Subsystem = GetSubsystem(WorldContextObject); IsValid(Subsystem))
	{
		Subsystem->OnEventTriggered(EventData);
	}
}

void UGameEventSubsystem::OnEventTriggered(const FGameEventData& EventData)
{
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
