
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FreeCameraComponent.h"

#include "ManipulationInputComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION INPUT COMPONENT                                         */
/************************************************************************/

// A component used to read manipulation-related inputs on a player controller.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API UManipulationInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Bind to an input component.
	void Bind(UInputComponent& InInputComponent);

	// Bind to a pawn.
	void Bind(APawn& InPawn);

private:

	// Spawn an entity by key.
	UFUNCTION(Exec)
	void SpawnEntity(const FName& InEntityKey);

};

// ==================================================================== //
