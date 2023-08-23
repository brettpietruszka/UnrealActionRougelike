// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTRangedAttack.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type USBTTRangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	Super::ExecuteTask(OwnerComp, NodeMemory);

	// This task should have the opponent shoot at the player character
	AAIController* TargetController = OwnerComp.GetAIOwner();
	if (ensure(TargetController))
	{
		ACharacter* AICharacter = Cast<ACharacter>(TargetController->GetPawn());
		if (!AICharacter)
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = AICharacter->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (!TargetActor)
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = AICharacter;
		if (!ensure(ProjectileClass))
		{
			return EBTNodeResult::Failed;
		}


		AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

		return Projectile ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
