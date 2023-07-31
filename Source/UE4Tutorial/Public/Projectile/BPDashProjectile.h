// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile/BPProjectileBase.h"
#include "BPDashProjectile.generated.h"

UCLASS()
class UE4TUTORIAL_API ABPDashProjectile : public ABPProjectileBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABPDashProjectile();

protected:

	FTimerHandle ShouldExplodeTimerHandle;

	UFUNCTION()
	void OnBulletShouldTeleportPlayerTimer();

	UFUNCTION()
	void OnBulletShouldExplodeTimer();

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// Delays
	float DetonateDelaySeconds = 1.0f;
	float TeleportDelaySeconds = 0.2f;

};
