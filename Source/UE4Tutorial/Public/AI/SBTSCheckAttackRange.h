// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SBTSCheckAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class UE4TUTORIAL_API USBTSCheckAttackRange : public UBTService
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
