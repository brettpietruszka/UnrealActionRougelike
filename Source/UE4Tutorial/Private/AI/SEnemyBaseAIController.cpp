// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SEnemyBaseAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


ASEnemyBaseAIController::ASEnemyBaseAIController()
{

}


void ASEnemyBaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr, please assign it.")))
	{
		RunBehaviorTree(BehaviorTree);

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		if (IsValid(PlayerPawn))
		{
			GetBlackboardComponent()->SetValueAsObject("TargetActor", PlayerPawn);
		}
	}

}
