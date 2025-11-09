// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameEventInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameEventSubsystem.generated.h"

struct FGameEventData;

DECLARE_LOG_CATEGORY_EXTERN(LogGameEvent, Log, All);

DECLARE_DELEGATE_OneParam(FOnTriggerEvents, const FGameEventData& Data);

/**
 * This is the subsystem that will dispatch all the events created in gameplay
 */
UCLASS()
class GAMEEVENTS_API UGameEventSubsystem : public UGameInstanceSubsystem, public IGameEventInterface
{
	GENERATED_BODY()
	
public:
	FOnTriggerEvents OnTriggerEvents;

	UFUNCTION(BlueprintCallable, Category="GameEvent", meta=(WorldContext="WorldContextObject", DisplayName="Trigger Event", CallableWithoutWorldContext))
	static void TriggerEvent(const UObject* WorldContextObject, const FGameEventData& EventData);
	
protected:
	virtual void OnEventTriggered(const FGameEventData& EventData) override;

private:
	static UGameEventSubsystem* GetSubsystem(const UObject* Object);

};
