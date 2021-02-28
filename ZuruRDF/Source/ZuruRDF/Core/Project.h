
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "Templates/SubclassOf.h"

#include "ProjectEntity.h"

#include "Project.generated.h"

// ==================================================================== //

/************************************************************************/
/* PROJECT                                                              */
/************************************************************************/

// Represents a project workspace.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(config = Game, notplaceable, BlueprintType, Blueprintable)
class ZURURDF_API AProject : public AInfo
{
	GENERATED_BODY()
	
public:

	// Spawn a new entity by class.
	FName SpawnEntity(TSubclassOf<AProjectEntity> InEntityClass);

private:

	// List of all entities in the project.
	UPROPERTY()
	TMap<FName, AProjectEntity*> Entities;

};

// ==================================================================== //
