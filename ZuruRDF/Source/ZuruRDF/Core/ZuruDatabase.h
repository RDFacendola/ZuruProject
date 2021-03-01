
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Info.h"
#include "Engine/DataTable.h"

#include "ZuruEntity.h"

#include "ZuruDatabase.generated.h"

// ==================================================================== //

/************************************************************************/
/* ZURU DATABASE ENTITY RECORD                                          */
/************************************************************************/

// Type of a single record in the entity database.
//
// @author Raffaele D. Facendola - February 2021.
USTRUCT(Blueprintable, BlueprintType)
struct FZuruDatabaseEntityRecord : public FTableRowBase
{
	GENERATED_BODY()

	// Entity class.
	// NOTE: This is not a brilliant idea as it would cause all subclasses being loaded
	//       at once, causing massive stalls. It's way better to use a soft class reference
	//       and load it manually.
	UPROPERTY(EditAnywhere)
	TSubclassOf<AZuruEntity> EntityClass;
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

	// Find a Zuru entity class from key.
	TSubclassOf<AZuruEntity> FindEntity(const FName& InKey) const;

private:

	// Maps each key to an entity subclass.
	UPROPERTY(EditAnywhere, Category = Database)
	UDataTable* Entities{ nullptr };

};

// ==================================================================== //
