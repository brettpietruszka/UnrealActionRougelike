// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPlayerCharacter.generated.h"


class UCameraComponent;
class USpringArmComponent;
class UBPInteractionComponent;
class UAnimMontage;
class UBPAttributeComponent;

UCLASS()
class UE4TUTORIAL_API ASPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> MagicProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BlackholeProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

protected:

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UBPInteractionComponent* InteractComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBPAttributeComponent* AttributeComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);
	void PrimaryAttack();
	void PrimaryInteract();

	void BlackholeAttack();
	void DashAttack();

	float PrimaryAttackDelay;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_DashAttacck;
	FTimerHandle TimerHandle_BlackholeAttack;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UBPAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float delta);

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void AttackTimer(TSubclassOf<AActor> ProjectileClass);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FTransform GetLookAtTransform(FVector StartLocation, FVector SpawnLocation);

	void GenerateProjectile(TSubclassOf<AActor> ProjectileClass, FTimerHandle TimerHandle);

};
