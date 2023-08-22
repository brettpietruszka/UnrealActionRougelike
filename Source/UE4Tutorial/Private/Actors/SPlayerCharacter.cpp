// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SPlayerCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BPInteractionComponent.h"
#include "Components/BPAttributeComponent.h"
#include "Animation/AnimMontage.h"


// Sets default values
ASPlayerCharacter::ASPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractComp = CreateDefaultSubobject<UBPInteractionComponent>("InteractComp");

	AttributeComponent = CreateDefaultSubobject<UBPAttributeComponent>("AttributeComp");


	GetCharacterMovement()->bOrientRotationToMovement = true;

	PrimaryAttackDelay = 0.2f;

	bUseControllerRotationYaw = false;

}

void ASPlayerCharacter::PostInitializeComponents()
{
	// Bind the on health change event
	Super::PostInitializeComponents();

	AttributeComponent->OnHealthChanged.AddDynamic(this, &ASPlayerCharacter::OnHealthChanged);
}

// Called when the game starts or when spawned
void ASPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	// -- Rotation Visualization -- //
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
	*/
}

void ASPlayerCharacter::MoveForward(float value) {

	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	AddMovementInput(ControlRot.Vector(), value);


}

void ASPlayerCharacter::MoveRight(float value) {

	// Get the 
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);
}

void ASPlayerCharacter::OnHealthChanged(AActor* InstigatorActor, UBPAttributeComponent* OwningComp, float NewHealth, float MaxHealth, float Delta)
{
	// See if the player becomes dead
	if (NewHealth < 0.0f && Delta < 0.0f)
	{

		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}



void ASPlayerCharacter::AttackTimer(TSubclassOf<AActor> ProjectileClass)
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;

	FTransform SpawnTM = GetLookAtTransform(CameraComp->GetComponentLocation(), HandLocation);

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

}

void ASPlayerCharacter::PrimaryAttack()
{
	GenerateProjectile(MagicProjectileClass, TimerHandle_PrimaryAttack);
}

void ASPlayerCharacter::PrimaryInteract()
{
	if (!InteractComp) {
		return;
	}

	InteractComp->PrimaryInteract();
}

void ASPlayerCharacter::BlackholeAttack()
{
	// 
	GenerateProjectile(BlackholeProjectileClass, TimerHandle_BlackholeAttack);

}

void ASPlayerCharacter::DashAttack()
{
	// Generate a Dash Projectile
	GenerateProjectile(DashProjectileClass, TimerHandle_DashAttacck);

}

void ASPlayerCharacter::GenerateProjectile(TSubclassOf<AActor> ProjectileClass, FTimerHandle TimerHandle)
{
	PlayAnimMontage(AttackAnim);

	FTimerDelegate ProjectileDelegate;
	ProjectileDelegate.BindUFunction(this, "AttackTimer", ProjectileClass);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, ProjectileDelegate, PrimaryAttackDelay, false);
}


// Called to bind functionality to input
void ASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &ASPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASPlayerCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("DashAttack", IE_Pressed, this, &ASPlayerCharacter::DashAttack);
	PlayerInputComponent->BindAction("BlackholeAttack", IE_Pressed, this, &ASPlayerCharacter::BlackholeAttack);


	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASPlayerCharacter::PrimaryInteract);


}

FTransform ASPlayerCharacter::GetLookAtTransform(FVector StartLocation, FVector SpawnLocation)
{
	// Run Line Trace and determine where hit should be
	FHitResult OutHit;

	FCollisionObjectQueryParams ObjParams;
	ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(20.0f);

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FVector EndLocation = StartLocation + GetControlRotation().Vector() * 5000.0f;

	if (GetWorld()->SweepSingleByObjectType(OutHit, StartLocation, EndLocation, FQuat::Identity, ObjParams, CollisionShape, Params))
	{
		EndLocation = OutHit.Location;
	}

	return FTransform(FRotationMatrix::MakeFromX(EndLocation - SpawnLocation).Rotator(), SpawnLocation);
}



