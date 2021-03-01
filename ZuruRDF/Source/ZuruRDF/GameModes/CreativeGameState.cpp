
// ==================================================================== //

#include "CreativeGameState.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE GAME STATE                                                  */
/************************************************************************/

ACreativeGameState::ACreativeGameState()
{
	ProjectComponent = CreateDefaultSubobject<UProjectComponent>(TEXT("Project"));
}

void ACreativeGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();
}

// ==================================================================== //
