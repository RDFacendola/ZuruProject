
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameModeBase.h"

#include "ManipulationComponent.h"

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

	// Bind to the game mode. Server-side only.
	void Bind(AGameModeBase& InGameMode);

	// Bind to an input component.
	void Bind(UInputComponent& InInputComponent);

	// Bind to a pawn.
	void Bind(APawn& InPawn);

private:

	// Spawn an entity by key.
	UFUNCTION(Exec)
	void SpawnEntity(const FName& InEntityKey);

	// Spawn an entity by key at given coordinates.
	void SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform);

	// Controlled pawn.
	UPROPERTY()
	APawn* Pawn{ nullptr };

	// The entity-manipulation component counterpart on the game mode.
	UPROPERTY()
	UManipulationComponent* ManipulationComponent{ nullptr };

};

// ==================================================================== //
