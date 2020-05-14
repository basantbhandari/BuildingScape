/// copyright,yesicbap@2020.


#include "Grabber.h"
#include "CollisionQueryParams.h"
#include "Engine/EngineTypes.h"

#define OUT

/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	/// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	/// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/// ...
}

///Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicHandlerComponent();
	FindInputComponents();
	
}

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	/// if physics handle is attached
	if (!physicsHandler) { return; }
    if(physicsHandler->GrabbedComponent){
	   /// move the object
		physicsHandler->SetTargetLocation(GetReachLineEnd());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab method is pressed from input component :) "));
	/// Line trace and check if we reach any actor with collision channel set
	/// if we hit something then attached physic handle
	if (GetFirstPhysicsBodyInReach().GetActor() != nullptr)
	{
		if (!physicsHandler) { return; }
		physicsHandler->GrabComponent(
			GetFirstPhysicsBodyInReach().GetComponent(),
			NAME_None,
			GetFirstPhysicsBodyInReach().GetComponent()->GetOwner()->GetActorLocation(),
			true
		);
	}
}

void UGrabber::Released()
{
	if (!physicsHandler) { return; }
	physicsHandler->ReleaseComponent();
}

///look for component attached physics handle
void UGrabber::FindPhysicHandlerComponent()
{
	physicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (physicsHandler == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is not found"), *(GetOwner()->GetName()));
	}
}

/// look for attached input component (appear only at run time) 
void UGrabber::FindInputComponents()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is not found"), *(GetOwner()->GetName()));
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Ray cast out to reach distance
	FHitResult Hit;
	FCollisionQueryParams traceParameter(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(Hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		traceParameter
	);
	return Hit;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	return(playerViewPointLocation + playerViewPointRotation.Vector() * Reach);
}

FVector UGrabber::GetReachLineStart()
{
	FVector playerViewPointLocation;
	FRotator playerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT playerViewPointLocation,
		OUT playerViewPointRotation
	);
	return(playerViewPointLocation );
}





