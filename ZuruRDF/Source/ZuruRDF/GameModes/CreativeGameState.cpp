
// ==================================================================== //

#include "CreativeGameState.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE GAME STATE                                                  */
/************************************************************************/

AZuruProject& ACreativeGameState::GetProject()
{
	return *Project;
}

void ACreativeGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	NewProject();
}

AZuruProject& ACreativeGameState::NewProject()
{
	auto SpawnParameters = FActorSpawnParameters{};

	SpawnParameters.bNoFail = true;

	Project = GetWorld()->SpawnActor<AZuruProject>(SpawnParameters);

	return *Project;
}

// ==================================================================== //
