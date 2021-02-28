
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "ZuruRDF/Core/Project.h"

#include "CreativeGameState.generated.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE GAME STATE                                                  */
/************************************************************************/

// Holds game-related infos during "creative" game mode.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API ACreativeGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	// Get the active project.
	AProject& GetProject();

	// Create a new project, discarding existing ones, if any.
	AProject& NewProject();

	void HandleBeginPlay() override;

private:

	// Active project.
	AProject* Project{ nullptr };
};

// ==================================================================== //
