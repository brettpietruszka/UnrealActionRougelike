// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SInteractableInterface.h"
#include "SItemChestActor.generated.h"

UCLASS()
class UE4TUTORIAL_API ASItemChestActor : public AActor, public ISInteractableInterface
{
	GENERATED_BODY()

	void Interact_Implementation(APawn* InstigatorPawn);

public:

	UPROPERTY(EditAnywhere)
	float TargetPitch;

	// Sets default values for this actor's properties
	ASItemChestActor();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
