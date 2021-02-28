
// ==================================================================== //

#include "ZuruDatabase.h"

// ==================================================================== //

#/************************************************************************/
/* ZURU DATABASE                                                        */
/************************************************************************/

TSubclassOf<AZuruEntity> UZuruDatabase::FindEntity(const FName& InKey) const
{
	if (auto Record = reinterpret_cast<FZuruDatabaseEntityRecord*>(Entities->FindRowUnchecked(InKey)))
	{
		return Record->EntityClass;
	}

	return {};
}

// ==================================================================== //
