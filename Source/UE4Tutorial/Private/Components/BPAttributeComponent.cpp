// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BPAttributeComponent.h"

// Sets default values for this component's properties
UBPAttributeComponent::UBPAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // for now regen will work off of timers
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// Set the health max to be the starting health
	HealthMax = Health;
}

bool UBPAttributeComponent::ApplyHealthChange(float HealthChange)
{
	if (IsValid(GetOwner()))
	{
		// Calculate the new health
		Health = FMath::Clamp(Health + HealthChange, 0.0f, HealthMax);

		// If we take damage, stop health regen
		if (HealthChange < 0)
		{
			// Need to reset any possible timer for rehealing
			GetWorld()->GetTimerManager().ClearTimer(StartHealthRegenTimerHandle);
			GetWorld()->GetTimerManager().ClearTimer(HeathRegenTimerHandle);
		}

		// If we are full on health, stop health regen
		if (Health == HealthMax)
		{
			GetWorld()->GetTimerManager().ClearTimer(HeathRegenTimerHandle);
		}
			
		//OnHealthChanged.Broadcast(nullptr,this, Health, HealthMax, HealthChange);

		GetWorld()->GetTimerManager().SetTimer(StartHealthRegenTimerHandle, this, &UBPAttributeComponent::StartRegenHealthTimer_Timer, TimeBeforeHealthRegenStartsSeconds, false);

		return true;
	}

	return false;
}


void UBPAttributeComponent::RegenHealth_Timer()
{
	// Continously apply a positive health change
	ApplyHealthChange(HealingRate);
}

void UBPAttributeComponent::StartRegenHealthTimer_Timer()
{
	GetWorld()->GetTimerManager().SetTimer(HeathRegenTimerHandle, this, &UBPAttributeComponent::RegenHealth_Timer, HealingTickTime, true);
}

// Called when the game starts
void UBPAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UBPAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}


// Called every frame
void UBPAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

