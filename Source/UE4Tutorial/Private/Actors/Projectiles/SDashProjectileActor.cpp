// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/SDashProjectileActor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASDashProjectileActor::ASDashProjectileActor()
{

	MovementComp->InitialSpeed = 1500.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;

	SphereComp->OnComponentHit.AddDynamic(this, &ASDashProjectileActor::OnActorHit);
}

// Called when the game starts or when spawned
void ASDashProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	// Set the timer for explode
	GetWorld()->GetTimerManager().SetTimer(ShouldExplodeTimerHandle, this, &ASDashProjectileActor::OnBulletShouldExplodeTimer, DetonateDelaySeconds);
}

void ASDashProjectileActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();


}

void ASDashProjectileActor::OnBulletShouldTeleportPlayerTimer()
{
	// Teleport the Instigator
	GetWorld()->GetTimerManager().ClearTimer(ShouldExplodeTimerHandle);

	AActor* ActorToTeleport = GetInstigator();
	if (ensure(IsValid(ActorToTeleport)))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}

	// Destroy the actor
	Destroy();
}

void ASDashProjectileActor::OnBulletShouldExplodeTimer()
{
	// Explode "" the actor
	GetWorld()->GetTimerManager().ClearTimer(ShouldExplodeTimerHandle);

	// Disable the rest of the effects/parts so it is effectively destroyed

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	// Start next timer
	GetWorld()->GetTimerManager().SetTimer(ShouldExplodeTimerHandle, this, &ASDashProjectileActor::OnBulletShouldTeleportPlayerTimer, TeleportDelaySeconds);
}

void ASDashProjectileActor::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Call OnBulletShouldExplodeTimer
	OnBulletShouldExplodeTimer();
}


// Called every frame
void ASDashProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

