
// ==================================================================== //

#include "ManipulationInputComponent.h"

#include "ZuruRDF/Core/ZuruGameInstance.h"
#include "ZuruRDF/Core/ZuruDatabase.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION INPUT COMPONENT                                         */
/************************************************************************/

void UManipulationInputComponent::Bind(UInputComponent& InInputComponent)
{

}

void UManipulationInputComponent::Bind(APawn& InPawn)
{

}

void UManipulationInputComponent::SpawnEntity(const FName& InEntityKey)
{
	auto World = GetWorld();

	check(World);

	auto GameInstance = World->GetGameInstance<UZuruGameInstance>();

	check(GameInstance);

	auto& Database = GameInstance->GetDatabase();

	if (auto EntityClass = Database.FindEntity(InEntityKey))
	{
		// Entity found.



	}
	else
	{
		// No such entity.

		auto Message = FString::Printf(TEXT("No entity with key '%s'."), *InEntityKey.ToString());

		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3.0f, FColor::Red, *Message);
	}
	
}

// ==================================================================== //

