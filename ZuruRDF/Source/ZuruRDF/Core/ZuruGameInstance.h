
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "ZuruDatabase.h"

#include "ZuruGameInstance.generated.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GAME INSTANCE                                                   */
/************************************************************************/

// Game instance class for all configuration stuffs that outlive worlds.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Core)
class ZURURDF_API UZuruGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	virtual void Init() override;

	// Get the singleton database instance.
	const UZuruDatabase& GetDatabase() const;

private:

	// The concrete database class.
	UPROPERTY(EditAnywhere, Category = Database)
	TSubclassOf<UZuruDatabase> DatabaseClass{ UZuruDatabase::StaticClass() };

	// The database singleton.
	UPROPERTY(transient)
	UZuruDatabase* Database{ nullptr };

};

// ==================================================================== //
