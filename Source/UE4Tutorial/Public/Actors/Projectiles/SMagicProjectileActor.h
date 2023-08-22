// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Projectiles/SProjectileBaseActor.h"
#include "SMagicProjectileActor.generated.h"

/**
 * 
 */
UCLASS()
class UE4TUTORIAL_API ASMagicProjectileActor : public ASProjectileBaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASMagicProjectileActor();

protected:

	UFUNCTION()
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
