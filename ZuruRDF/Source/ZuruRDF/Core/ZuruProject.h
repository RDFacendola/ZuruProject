
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "Templates/SubclassOf.h"

#include "ZuruEntity.h"

#include "ZuruProject.generated.h"

// ==================================================================== //

/************************************************************************/
/* ZURU PROJECT                                                         */
/************************************************************************/

// Represents a Zuru project workspace.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(config = Game, notplaceable, BlueprintType, Blueprintable)
class ZURURDF_API AZuruProject : public AInfo
{
	GENERATED_BODY()
	
public:

	// Spawn a new entity by class.
	FName SpawnEntity(TSubclassOf<AZuruEntity> InEntityClass);

private:

	// List of all entities in the project.
	UPROPERTY()
	TMap<FName, AZuruEntity*> Entities;

};

// ==================================================================== //
