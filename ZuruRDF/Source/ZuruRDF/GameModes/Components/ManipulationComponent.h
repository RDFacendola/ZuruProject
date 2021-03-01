
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FreeCameraComponent.h"

#include "ManipulationComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION COMPONENT                                               */
/************************************************************************/

// A component used to handle entity-manipulation-related actions.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS()
class ZURURDF_API UManipulationComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Spawn an entity by key at given coordinates.
	void SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform);

private:

};

// ==================================================================== //
