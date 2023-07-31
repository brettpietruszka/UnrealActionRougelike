// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BPBTService_CheckAttacksRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void UBPBTService_CheckAttacksRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check the distance between the AI Pawn and target Actor

	UBlackboardComponent* BlackboardComp= OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboardComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* TargetController = OwnerComp.GetAIOwner();
			if (ensure(TargetController))
			{
				APawn* AIPawn = TargetController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithinRange = DistanceTo < 1500.0f;

					bool bHasLOS = false;
					if (bWithinRange)
					{
						bHasLOS = TargetController->LineOfSightTo(TargetActor);
					}

					BlackboardComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, bWithinRange && bHasLOS);
				}
			}

		}
	}

}
