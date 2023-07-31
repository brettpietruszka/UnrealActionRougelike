// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BPDashProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABPDashProjectile::ABPDashProjectile()
{

	MovementComp->InitialSpeed = 1500.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;

	SphereComp->OnComponentHit.AddDynamic(this, &ABPDashProjectile::OnActorHit);
}

// Called when the game starts or when spawned
void ABPDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Set the timer for explode
	GetWorld()->GetTimerManager().SetTimer(ShouldExplodeTimerHandle, this, &ABPDashProjectile::OnBulletShouldExplodeTimer, DetonateDelaySeconds);
}

void ABPDashProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
}

void ABPDashProjectile::OnBulletShouldTeleportPlayerTimer()
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

void ABPDashProjectile::OnBulletShouldExplodeTimer()
{
	// Explode "" the actor
	GetWorld()->GetTimerManager().ClearTimer(ShouldExplodeTimerHandle);

	// Disable the rest of the effects/parts so it is effectively destroyed

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	// Start next timer
	GetWorld()->GetTimerManager().SetTimer(ShouldExplodeTimerHandle, this, &ABPDashProjectile::OnBulletShouldTeleportPlayerTimer, TeleportDelaySeconds);
}

void ABPDashProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Call OnBulletShouldExplodeTimer
	OnBulletShouldExplodeTimer();
}


// Called every frame
void ABPDashProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

