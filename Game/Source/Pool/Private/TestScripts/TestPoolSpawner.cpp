// Fill out your copyright notice in the Description page of Project Settings.


#include "TestScripts/TestPoolSpawner.h"

#include "PoolSubsystem.h"

void ATestPoolSpawner::BeginPlay()
{
	Super::BeginPlay();

	auto& TimerManager = GetWorld()->GetTimerManager();

	FTimerHandle TimerHandle;
	TimerManager.SetTimer(TimerHandle, FTimerDelegate::CreateUObject(this, &ATestPoolSpawner::TimerCompleted), 1.f, false);
}

void ATestPoolSpawner::InitializeActor(AActor* Actor)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, "Initializing Actor");
}

void ATestPoolSpawner::PlaceActor(AActor* Actor, const int32 IndexLocation)
{
	GEngine->AddOnScreenDebugMessage(-1, 30.f, FColor::Red, "Place Actor");

	Actor->SetActorLocation(SpawnLocations[IndexLocation]->GetActorLocation(), false, nullptr, ETeleportType::ResetPhysics);
}

void ATestPoolSpawner::TimerCompleted()
{
	auto* PoolSubsystem = GetWorld()->GetSubsystem<UPoolSubsystem>();
	for (int i = 0; i < SpawnLocations.Num(); i++)
	{
		FActorInitializationParams Params;
		Params.InitializeActor.BindUObject(this, &ATestPoolSpawner::InitializeActor);
		Params.PlaceActor.BindUObject(this, &ATestPoolSpawner::PlaceActor, i);
	
		PoolSubsystem->SpawnActor(ActorTagToSpawn, Params);
	}}
