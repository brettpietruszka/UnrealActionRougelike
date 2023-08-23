// Fill out your copyright notice in the Description page of Project Settings.


#include "BPTargetDummy.h"
#include "Components/BPAttributeComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABPTargetDummy::ABPTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	AttribComp = CreateDefaultSubobject<UBPAttributeComponent>("AttribComp");

	//AttribComp->OnHealthChanged.AddDynamic(this, &ABPTargetDummy::OnHealthChanged);

}

void ABPTargetDummy::OnHealthChanged(AActor* InstigatorActor, UBPAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float delta)
{
	if (delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->GetTimeSeconds());
	}
}

// Called when the game starts or when spawned
void ABPTargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABPTargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

