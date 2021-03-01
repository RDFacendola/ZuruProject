
// ==================================================================== //

#include "ManipulationComponent.h"

#include "ZuruRDF/Core/ZuruGameInstance.h"
#include "ZuruRDF/Core/ZuruEntity.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION COMPONENT                                               */
/************************************************************************/

void UManipulationComponent::Bind(AGameStateBase& InGameState)
{
	ProjectComponent = InGameState.FindComponentByClass<UProjectComponent>();
}

void UManipulationComponent::SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform)
{
	if (ProjectComponent)
	{
		ProjectComponent->SpawnEntityAt(InEntityKey, InEntityTransform);
	}
}

// ==================================================================== //

