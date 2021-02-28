
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "ProjectEntity.h"
#include "Engine/DataTable.h"

#include "ZuruDatabase.generated.h"

// ==================================================================== //

/************************************************************************/
/* ZURU DATABASE ENTITY RECORD                                          */
/************************************************************************/

USTRUCT(Blueprintable, BlueprintType)
struct FZuruDatabaseEntityRecord
{
	GENERATED_BODY()

	// Entity key.
	FName Key;

	// Dummy field.
	int32 Dummy;
};

/************************************************************************/
/* ZURU DATABASE                                                        */
/************************************************************************/

// Represents a database containing all spawnable entities.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Database)
class ZURURDF_API UZuruDatabase : public UObject
{
	GENERATED_BODY()
	
public:

	// Find a project entity class from key.
	TSubclassOf<AProjectEntity> FindEntity(const FName& InKey) const;

private:

	// Maps each key to an entity subclass.
	UPROPERTY(EditAnywhere, Category = Database)
	UDataTable* Entities{ nullptr };

};

// ==================================================================== //
