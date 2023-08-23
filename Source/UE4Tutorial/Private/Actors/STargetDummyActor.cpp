// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/STargetDummyActor.h"
#include "Components/SAttributeComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASTargetDummyActor::ASTargetDummyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttribComp = CreateDefaultSubobject<USAttributeComponent>("AttribComp");

	AttribComp->OnHealthChanged.AddDynamic(this, &ASTargetDummyActor::OnHealthChanged);

}

void ASTargetDummyActor::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float delta)
{
	if (delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
	}
}

// Called when the game starts or when spawned
void ASTargetDummyActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASTargetDummyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

