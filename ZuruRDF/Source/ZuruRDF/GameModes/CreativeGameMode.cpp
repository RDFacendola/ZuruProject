
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
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = TG_PrePhysics;
    PrimaryActorTick.bTickEvenWhenPaused = true;

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

void ACreativeGameMode::Tick(float InDeltaSeconds)
{
    Super::Tick(InDeltaSeconds);

    ManipulationComponent->Advance(InDeltaSeconds);
}

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //

