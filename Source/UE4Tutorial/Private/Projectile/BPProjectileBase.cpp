// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BPProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABPProjectileBase::ABPProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp; // added this

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
}

void ABPProjectileBase::OnInFlight_Timer()
{
	if (IsValid(InFlightSound))
	{
		UGameplayStatics::PlaySoundAtLocation(this, InFlightSound, GetActorLocation());
	}
}

void ABPProjectileBase::PostInitializeComponents()
{
	// Do Nothing so that base classes can implement
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ABPProjectileBase::OnProjectileHit);

	GetWorld()->GetTimerManager().SetTimer(InFlightTimerHandle, this, &ABPProjectileBase::OnInFlight_Timer, 0.2, true);
}

void ABPProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	// Explode !!
	Explode_Implementation();

}

void ABPProjectileBase::Explode_Implementation()
{

	GetWorld()->GetTimerManager().ClearTimer(InFlightTimerHandle);

	if (IsValid(this)) // IsPendingKill()
	{

		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

		if (IsValid(ImpactSound))
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Impact Sound not set for magic projectile"));
		}

		Destroy();
	}
}

// Called when the game starts or when spawned
void ABPProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	
}

// Called every frame
void ABPProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

