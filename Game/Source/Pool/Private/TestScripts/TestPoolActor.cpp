// Fill out your copyright notice in the Description page of Project Settings.


#include "TestScripts/TestPoolActor.h"


// Sets default values
ATestPoolActor::ATestPoolActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestPoolActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestPoolActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

