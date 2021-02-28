
// ==================================================================== //

#include "CreativeGameState.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE GAME STATE                                                  */
/************************************************************************/

AProject& ACreativeGameState::GetProject()
{
	return *Project;
}

void ACreativeGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	NewProject();
}

AProject& ACreativeGameState::NewProject()
{
	auto SpawnParameters = FActorSpawnParameters{};

	SpawnParameters.bNoFail = true;

	Project = GetWorld()->SpawnActor<AProject>(SpawnParameters);

	return *Project;
}

// ==================================================================== //
