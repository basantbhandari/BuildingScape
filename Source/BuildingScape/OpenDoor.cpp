// copyright,yesicbap@2020.


#include "OpenDoor.h"
#include "Gameframework/Actor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}



// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//finding the owner actor
	Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(GetTotalMassOfActorOnPlate() > ThresholdValueForTriggerMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}



float UOpenDoor::GetTotalMassOfActorOnPlate()
{
	float totalMass = 0.0f;
	//find the all overlapping actor
	TArray<AActor*> OverlappingActors;
	if (!PresserPlate) { return 1.0f; }
	PresserPlate->GetOverlappingActors(OUT OverlappingActors);
	
	//iterate through them and sum up their total masses
	for(const auto & actor: OverlappingActors)
	{
		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Overlaped actor name = %s"), *(actor->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("Overlaped Total mass = %f"), totalMass);


	return(totalMass);
}












