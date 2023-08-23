// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FOnHealthChanged, AActor*, InstigatorActor, USAttributeComponent*, OwningComp, float, NewHealth, float, HealthMax, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4TUTORIAL_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USAttributeComponent();


	// Change Health
	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChange(float HealthChange);

protected:


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (UIMin = 1, ClampMin = 1), Category = "Attributes")
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = 1, ClampMin = 1), Category = "Attributes")
	float HealthMax = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = 1, ClampMin = 1), Category = "Attributes")
	float HealingRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = 1, ClampMin = 1), Category = "Attributes")
	float HealingTickTime = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = 1, ClampMin = 1), Category = "Attributes")
	float TimeBeforeHealthRegenStartsSeconds = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	bool bAutomaticallyRegenHealth = true;

	/* Regen the players health by HealingRate each tick until Health is HealthMax */
	UFUNCTION()
	void RegenHealth_Timer();

	/* After not taking damage for TimeBeforeHealthRegenStartsSeconds, begin the timer
	that regens your health until you are full on health */
	UFUNCTION()
	void StartRegenHealthTimer_Timer();

	FTimerHandle HeathRegenTimerHandle;

	FTimerHandle StartHealthRegenTimerHandle;

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
