
// ==================================================================== //

#include "ProjectComponent.h"

#include "ZuruRDF/Core/ZuruGameInstance.h"

// ==================================================================== //

/************************************************************************/
/* PROJECT COMPONENT                                                    */
/************************************************************************/

void UProjectComponent::SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform)
{
	auto World = GetWorld();

	check(World);

	auto GameInstance = World->GetGameInstance<UZuruGameInstance>();

	check(GameInstance);

	auto& Database = GameInstance->GetDatabase();

	if (auto EntityClass = Database.FindEntity(InEntityKey))
	{
		// Entity found.

		auto SpawnParameters = FActorSpawnParameters{};

		SpawnParameters.bNoFail = true;

		auto Entity = World->SpawnActor<AZuruEntity>(EntityClass, InEntityTransform, SpawnParameters);

		Entities.Emplace(Entity);
	}
	else
	{
		// No such entity.

		auto Message = FString::Printf(TEXT("No entity with key '%s'."), *InEntityKey.ToString());

		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Red, *Message);
	}
}

// ==================================================================== //

