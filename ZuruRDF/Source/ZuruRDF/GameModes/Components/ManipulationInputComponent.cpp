
// ==================================================================== //

#include "ManipulationInputComponent.h"

#include "ZuruRDF/Core/ZuruGameInstance.h"
#include "ZuruRDF/Core/ZuruDatabase.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION INPUT COMPONENT                                         */
/************************************************************************/

void UManipulationInputComponent::Bind(AGameModeBase& InGameMode)
{
	ManipulationComponent = InGameMode.FindComponentByClass<UManipulationComponent>();
}

void UManipulationInputComponent::Bind(UInputComponent& InInputComponent)
{

}

void UManipulationInputComponent::Bind(APawn& InPawn)
{
	Pawn = &InPawn;
}

void UManipulationInputComponent::SpawnEntity(const FName& InEntityKey)
{
	SpawnEntityAt(InEntityKey, Pawn->GetActorTransform());
}

void UManipulationInputComponent::SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform)
{
	if (ManipulationComponent)
	{
		ManipulationComponent->SpawnEntityAt(InEntityKey, InEntityTransform);
	}
}

// ==================================================================== //

