// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BPBlackholeProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ABPBlackholeProjectile::ABPBlackholeProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	//SphereComp->SetSimulatePhysics(true);
	SphereComp->SetCollisionProfileName("OverlapAllDynamic");

	MovementComp->InitialSpeed = 1500.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.0f;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->Radius = 1000.0f;
	RadialForceComp->ForceStrength = -2000000.0f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);
	RadialForceComp->AddCollisionChannelToAffect(ECC_WorldStatic);
	RadialForceComp->SetupAttachment(SphereComp);

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABPBlackholeProjectile::OnActorOverlap);
}

void ABPBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ABPBlackholeProjectile::OnActorOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// We want to destroy the other actor !!!
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
	
}

// Called when the game starts or when spawned
void ABPBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABPBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RadialForceComp->FireImpulse();

}

