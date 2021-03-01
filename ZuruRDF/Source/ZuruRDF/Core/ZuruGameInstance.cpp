
// ==================================================================== //

#include "ZuruGameInstance.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GAME INSTANCE                                                   */
/************************************************************************/

void UZuruGameInstance::Init()
{
	Super::Init();

	// NOTE: This is ok if the number of records is negligible, otherwise is a big "no".

	Database = NewObject<UZuruDatabase>(this, DatabaseClass, TEXT("ZuruDatabase"), RF_Transient);
}

const UZuruDatabase& UZuruGameInstance::GetDatabase() const
{
	check(Database);

	return *Database;
}

// ==================================================================== //

