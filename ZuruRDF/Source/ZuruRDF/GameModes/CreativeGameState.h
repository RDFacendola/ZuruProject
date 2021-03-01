
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "Components/ProjectComponent.h"

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

	// Create a new creative game state.
	ACreativeGameState();

	void HandleBeginPlay() override;

private:

	// The actual project.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UProjectComponent* ProjectComponent{ nullptr };

};

// ==================================================================== //
