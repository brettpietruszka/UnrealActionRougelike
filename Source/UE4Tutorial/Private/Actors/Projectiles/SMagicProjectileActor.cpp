// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/SMagicProjectileActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BPAttributeComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ASMagicProjectileActor::ASMagicProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectileActor::OnActorOverlap);

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

	//SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//SphereComp->SetCollisonResponseToChannel(ECC_Pawn, ECR_Overlap);

	MovementComp->InitialSpeed = 2500.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ASMagicProjectileActor::BeginPlay()
{
	Super::BeginPlay();

}

void ASMagicProjectileActor::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// We want to damage the player
	if (IsValid(OtherActor) && OtherActor != GetInstigator())
	{
		UBPAttributeComponent* AttribComp = Cast<UBPAttributeComponent>(OtherActor->GetComponentByClass(UBPAttributeComponent::StaticClass()));
		if (IsValid(AttribComp))
		{
			AttribComp->ApplyHealthChange(-10.0f);

			Explode();
		}

	}
}

void ASMagicProjectileActor::PostInitializeComponents()
{

	Super::PostInitializeComponents();
}

// Called every frame
void ASMagicProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

