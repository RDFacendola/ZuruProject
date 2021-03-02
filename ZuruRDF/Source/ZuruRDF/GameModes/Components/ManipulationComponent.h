
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameStateBase.h"

#include "FreeCameraComponent.h"
#include "ProjectComponent.h"

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

	// Bind the component to a game state.
	void Bind(AGameStateBase& InGameState);

	// Spawn an entity by key at given coordinates.
	void SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform);

private:

	// The project the entities manipulated by this component exist into.
	UPROPERTY()
	UProjectComponent* ProjectComponent{ nullptr };

};

// ==================================================================== //