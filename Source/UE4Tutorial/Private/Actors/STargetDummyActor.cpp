// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/STargetDummyActor.h"

// Sets default values
ASTargetDummyActor::ASTargetDummyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASTargetDummyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTargetDummyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

