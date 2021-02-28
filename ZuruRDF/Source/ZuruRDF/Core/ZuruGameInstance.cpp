
// ==================================================================== //

#include "ZuruGameInstance.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GAME INSTANCE                                                   */
/************************************************************************/

PRAGMA_DISABLE_OPTIMIZATION

void UZuruGameInstance::PostInitProperties()
{
	Super::PostInitProperties();

	Database = NewObject<UZuruDatabase>(this, DatabaseClass, TEXT("Database"));
}

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //

