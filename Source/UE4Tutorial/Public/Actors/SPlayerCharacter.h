// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPlayerCharacter.generated.h"

class ASProjectileBaseActor;
class UCameraComponent;
class USpringArmComponent;
class UBPInteractionComponent;
class UAnimMontage;
class USAttributeComponent;

DECLARE_DYNAMIC_DELEGATE_OneParam(FProjectileDelegate, TSubclassOf<ASProjectileBaseActor>, ProjectileClass);

UCLASS()
class UE4TUTORIAL_API ASPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPlayerCharacter();

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBaseActor> MagicProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBaseActor> DashProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<ASProjectileBaseActor> BlackholeProjectileClass;

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
	USAttributeComponent* AttributeComponent;

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
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float delta);

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void AttackTimer(TSubclassOf<ASProjectileBaseActor> ProjectileClass);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FTransform GetLookAtTransform(FVector StartLocation, FVector SpawnLocation);

	void GenerateProjectile(TSubclassOf<ASProjectileBaseActor> ProjectileClass, FTimerHandle TimerHandle);

};
