// Fill out your copyright notice in the Description page of Project Settings.


#include "BPItemChest.h"


// Sets default values
ABPItemChest::ABPItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110.0f;
}

void ABPItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}


// Called when the game starts or when spawned
void ABPItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABPItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

