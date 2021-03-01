
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Components/ManipulationComponent.h"

#include "CreativeGameMode.generated.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE GAME MODE                                                   */
/************************************************************************/

// A creative game mode where the user can place, remove and update a room.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API ACreativeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ACreativeGameMode();

private:
	
	// Handles entity-manipulation-related commands.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UManipulationComponent* ManipulationComponent{ nullptr };

};

// ==================================================================== //
