// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "TestPoolSpawner.generated.h"

UCLASS()
class POOL_API ATestPoolSpawner : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FGameplayTag ActorTagToSpawn;
	
	UPROPERTY(EditAnywhere)
	TArray<AActor*> SpawnLocations;
	
	virtual void BeginPlay() override;

private:
	void InitializeActor(AActor* Actor);
	void PlaceActor(AActor* Actor, const int32 IndexLocation);

	void TimerCompleted();
};
