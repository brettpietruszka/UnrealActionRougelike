// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/SEnemyBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
ASEnemyBaseCharacter::ASEnemyBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensing");

}

// Called when the game starts or when spawned
void ASEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ASEnemyBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensing->OnSeePawn.AddDynamic(this, &ASEnemyBaseCharacter::OnSeePawn);
}

void ASEnemyBaseCharacter::OnSeePawn(APawn* Pawn)
{
	AAIController* AIC = Cast<AAIController>(GetController());

	if (AIC)
	{
		UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();

		if (BBComp)
		{
			BBComp->SetValueAsObject("TargetActor", Pawn);

			DrawDebugString(GetWorld(), GetActorLocation(), "PAWN SEEN", nullptr, FColor::Red, 1.0f);
		}
	}
}

// Called every frame
void ASEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASEnemyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

