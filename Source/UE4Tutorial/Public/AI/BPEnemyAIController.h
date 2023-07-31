// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BPEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4TUTORIAL_API ABPEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABPEnemyAIController();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;
	
};
