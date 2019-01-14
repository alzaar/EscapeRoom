// Fill out your copyright notice in the Description page of Project Settings.

#include "GB.h"


// Sets default values for this component's properties
UGB::UGB()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGB::BeginPlay()
{
	Super::BeginPlay();
	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// ...
	if (PhysicsHandleComponent) 
	{

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing a physics component"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	// ...
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found."));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGB::Grab);
		InputComponent->BindAction("Grab", IE_Released , this, &UGB::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing a physics component"), *GetOwner()->GetName());
	}
	
}

void UGB::Grab() {
	UE_LOG(LogTemp, Error, TEXT("Grab Presses"));
}

void UGB::Release() {
	UE_LOG(LogTemp, Error, TEXT("Grab Released"));
}

// Called every frame
void UGB::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT("Location: %s    Rotation: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());

	FVector LineTraceDirection = PlayerViewPointRotation.Vector();
	FVector LineTraceEnd = PlayerViewPointLocation + LineTraceDirection * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line Trace hit %s"), *(ActorHit->GetName()));
	}
	
}

