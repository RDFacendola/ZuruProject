
// ==================================================================== //

#include "ManipulationInputComponent.h"

#include "ZuruRDF/GameModes/Inputs/ManipulationInputs.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION INPUT COMPONENT                                         */
/************************************************************************/

void UManipulationInputComponent::Bind(AGameModeBase& InGameMode)
{
    ManipulationComponent = InGameMode.FindComponentByClass<UManipulationComponent>();
}

void UManipulationInputComponent::Bind(APlayerController& InPlayerController)
{
    InPlayerController.bShowMouseCursor = true;
    
    PlayerController = &InPlayerController;
}

void UManipulationInputComponent::Bind(UInputComponent& InInputComponent)
{
    InInputComponent.BindAction(FManipulationInputs::kSelectEntity, IE_Pressed, this, &UManipulationInputComponent::OnSelectEntityPressed);
    InInputComponent.BindAction(FManipulationInputs::kSelectEntity, IE_Released, this, &UManipulationInputComponent::OnSelectEntityReleased);
    InInputComponent.BindAction(FManipulationInputs::kSelectAdditionalEntity, IE_Pressed, this, &UManipulationInputComponent::OnSelectAdditionalEntityPressed);
    InInputComponent.BindAction(FManipulationInputs::kSelectAdditionalEntity, IE_Released, this, &UManipulationInputComponent::OnSelectAdditionalEntityReleased);
}

void UManipulationInputComponent::Bind(APawn& InPawn)
{
    Pawn = &InPawn;
}

void UManipulationInputComponent::OnSelectEntityPressed()
{
    if (bSelectEntityEnabled)
    {
        bSelectEntityEnabled = false;
    }
}

void UManipulationInputComponent::OnSelectEntityReleased()
{
    bSelectEntityEnabled = true;
}

void UManipulationInputComponent::OnSelectAdditionalEntityPressed()
{
    if (bSelectAdditionalEntityEnabled)
    {
        bSelectAdditionalEntityEnabled = false;
    }
}

void UManipulationInputComponent::OnSelectAdditionalEntityReleased()
{
    bSelectAdditionalEntityEnabled = true;
}

void UManipulationInputComponent::SpawnEntity(const FName& InEntityKey)
{
    SpawnEntityAt(InEntityKey, Pawn->GetActorTransform());
}

void UManipulationInputComponent::SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform)
{
    if (ManipulationComponent)
    {
        ManipulationComponent->SpawnEntityAt(InEntityKey, InEntityTransform);
    }
}

// ==================================================================== //

