// copyright,yesicbap@2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGSCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//variable to define how long the debug line should be
	float Reach = 100.f;

	UPhysicsHandleComponent* physicsHandler = nullptr;
	UInputComponent* InputComponent = nullptr;

	//Ray-cast and grab what's in reach
	void Grab();
	//called when Grab is released
	void Released();
	//find (assumed) attached physic handle
	void FindPhysicHandlerComponent();
	//find (assumed) attached input components
	void FindInputComponents();
    // find the physics body and reach
	FHitResult GetFirstPhysicsBodyInReach();
	// getting reach line start
	FVector GetReachLineStart();
	// getting reach line end
	FVector GetReachLineEnd();
		
};




