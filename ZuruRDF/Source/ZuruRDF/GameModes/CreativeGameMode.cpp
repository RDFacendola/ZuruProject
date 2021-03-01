
// ==================================================================== //

#include "CreativeGameMode.h"
#include "CreativeGameState.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE GAME MODE                                                   */
/************************************************************************/

PRAGMA_DISABLE_OPTIMIZATION

ACreativeGameMode::ACreativeGameMode()
{
	ManipulationComponent = CreateDefaultSubobject<UManipulationComponent>(TEXT("Manipulation"));
}

void ACreativeGameMode::InitGameState()
{
	Super::InitGameState();

	auto CreativeGameState = GetGameState<ACreativeGameState>();

	check(CreativeGameState);

	// Bind all game mode components to the game state.

	ManipulationComponent->Bind(*CreativeGameState);
}

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //

