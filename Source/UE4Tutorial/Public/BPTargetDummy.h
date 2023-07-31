// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BPTargetDummy.generated.h"

class UStaticMeshComponent;
class UBPAttributeComponent;

UCLASS()
class UE4TUTORIAL_API ABPTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABPTargetDummy();

protected:


	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	UBPAttributeComponent* AttribComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UBPAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float delta);


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
