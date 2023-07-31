// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BPBTService_CheckAttacksRange.generated.h"

/**
 * 
 */
UCLASS()
class UE4TUTORIAL_API UBPBTService_CheckAttacksRange : public UBTService
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = "AI")
	FBlackboardKeySelector AttackRangeKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
