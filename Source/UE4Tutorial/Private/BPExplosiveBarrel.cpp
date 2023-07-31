// Fill out your copyright notice in the Description page of Project Settings.


#include "BPExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ABPExplosiveBarrel::ABPExplosiveBarrel()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh; // rename to have comp at end

	ImpactForce = CreateDefaultSubobject<URadialForceComponent>("ImpactForce");
	ImpactForce->SetupAttachment(StaticMesh);
}

void ABPExplosiveBarrel::PostInitializeComponents() {
	Super::PostInitializeComponents();

	// Initialize properties here so stuff still works ???
	StaticMesh->SetSimulatePhysics(true);
	

	// eliminate default force
	ImpactForce->SetAutoActivate(false);

	// set radial force properties
	ImpactForce->Radius = 750.0f;
	ImpactForce->ImpulseStrength = 2500.0f;
	ImpactForce->bImpulseVelChange = true; // ignore current velocity and mass of object


	// add collisionchannel
	ImpactForce->AddCollisionChannelToAffect(ECC_WorldDynamic); // check ECC, changes default

	StaticMesh->OnComponentHit.AddDynamic(this, &ABPExplosiveBarrel::OnActorHit);
	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ABPExplosiveBarrel::OnActorOverlap);
}


void ABPExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {

	ImpactForce->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit reached (ExplosiveBarrel)"));
	
	FString CombinedString = FString::Printf(TEXT("Hit at Location %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);

}

void ABPExplosiveBarrel::OnActorOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ImpactForce->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnActorOverlap reached (ExplosiveBarrel)"));

}
