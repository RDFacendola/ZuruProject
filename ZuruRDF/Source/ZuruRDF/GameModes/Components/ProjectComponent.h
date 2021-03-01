
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ZuruRDF/Core/ZuruEntity.h"

#include "ProjectComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* PROJECT COMPONENT                                                    */
/************************************************************************/

// A component used to manage a project.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS()
class ZURURDF_API UProjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Spawn an entity by key at given coordinates.
	void SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform);

private:

	// List of entities spawned so far.
	UPROPERTY()
	TArray<AZuruEntity*> Entities;

};

// ==================================================================== //
