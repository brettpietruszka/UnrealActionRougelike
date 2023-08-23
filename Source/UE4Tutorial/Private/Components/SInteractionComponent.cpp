// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SInteractionComponent.h"
#include "SInteractableInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);


	FVector End;

	FVector EyeLocation;
	FRotator EyeRotation;

	AActor* MyOwner = GetOwner();
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	End = EyeLocation + (EyeRotation.Vector() * 1000);

	/*FHitResult Hit;
	bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);

	if (AActor* HitActor = Hit.GetActor())
	{
		if (HitActor->Implements<UBPGameplayInterface>())
		{
			IBPGameplayInterface::Execute_Interact(HitActor, Cast<APawn>(MyOwner));
		}
	}*/

	float Radius = 30.0f;

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);



	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (const FHitResult& Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<USInteractableInterface>())
			{
				ISInteractableInterface::Execute_Interact(HitActor, Cast<APawn>(MyOwner));
			}
		}

		//DrawDebugSphere(GetWorld(), Hit.Location, Radius, 32, LineColor, false, 2.0f);
		break;
	}/*

	if (bBlockingHit)
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Green, false, 2.0f, 0, 2.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), EyeLocation, End, FColor::Orange, false, 2.0f, 0, 2.0f);
	}
	*/

}

