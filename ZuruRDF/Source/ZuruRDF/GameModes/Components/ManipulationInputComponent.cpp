
// ==================================================================== //

#include "ManipulationInputComponent.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION INPUT COMPONENT                                         */
/************************************************************************/

void UManipulationInputComponent::Bind(UInputComponent& InInputComponent)
{

}

void UManipulationInputComponent::Bind(APawn& InPawn)
{

}

void UManipulationInputComponent::SpawnEntity(const FName& InEntityKey)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Red, TEXT("NOT YET IMPLEMENTED!"));
}

// ==================================================================== //

