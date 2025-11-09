// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/EventConverter.h"

#include "CycleDataTypes.h"
#include "GameEventDataTypes.h"
#include "GameEventSubsystem.h"

void UEventConverter::TriggerCycleEvent(const UObject* WorldContextObject, const FCycleDefinition& CycleDefinition)
{
	FGameEventData EventData;
	EventData.EventTag = CycleDefinition.Event;
	EventData.TagParameters.AppendTags(CycleDefinition.EventTags);
	EventData.Parameters.Add(TAG_Cycle_Parameter_CycleIndex, CycleDefinition.CycleIndex);
	EventData.Parameters.Add(TAG_Cycle_Parameter_StartTime, CycleDefinition.StartTime);
	EventData.Parameters.Add(TAG_Cycle_Parameter_CurrentTime, CycleDefinition.CurrentTime);
	EventData.Parameters.Add(TAG_Cycle_Parameter_Multiplier, CycleDefinition.Multiplier);
	UGameEventSubsystem::TriggerEvent(WorldContextObject, EventData);

}
