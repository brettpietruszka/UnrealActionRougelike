// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Projectiles/SProjectileBaseActor.h"
#include "SBlackholeProjectileActor.generated.h"


class URadialForceComponent;

/**
 * 
 */
UCLASS()
class UE4TUTORIAL_API ASBlackholeProjectileActor : public ASProjectileBaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASBlackholeProjectileActor();

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForceComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
