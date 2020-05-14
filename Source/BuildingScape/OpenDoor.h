// copyright,yesicbap@2020.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "OpenDoor.generated.h"

//creating new class which help to expose cpp class event to blueprint 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvents);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGSCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	//creating instance of cpp to blueprint
	UPROPERTY(BlueprintAssignable)
	FDoorEvents OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvents OnClose;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PresserPlate = nullptr;

	
	UPROPERTY(EditAnywhere)
	float ThresholdValueForTriggerMass = 30.f;


	AActor* Owner = nullptr;
	//function that returns the total mass of actor on plate
	float GetTotalMassOfActorOnPlate();
	
};

















