// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BPMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BPAttributeComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ABPMagicProjectile::ABPMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABPMagicProjectile::OnActorOverlap);

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	
	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComp->SetCollisonResponseToChannel(ECC_Pawn, ECR_Overlap);

	MovementComp->InitialSpeed = 2500.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ABPMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABPMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// We want to damage the player
	if (IsValid(OtherActor) && OtherActor != GetInstigator())
	{
		UBPAttributeComponent* AttribComp= Cast<UBPAttributeComponent>(OtherActor->GetComponentByClass(UBPAttributeComponent::StaticClass()));
		if (IsValid(AttribComp))
		{
			AttribComp->ApplyHealthChange(-10.0f);

			Explode();
		}

	}
}

void ABPMagicProjectile::PostInitializeComponents()
{

	Super::PostInitializeComponents();
}

// Called every frame
void ABPMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

