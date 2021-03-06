
// ==================================================================== //

#include "ManipulationViewComponent.h"

#include "Camera/CameraComponent.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

/************************************************************************/
/* MANIPULATION VIEW COMPONENT                                          */
/************************************************************************/

void UManipulationViewComponent::Bind(APlayerController& InPlayerController)
{

}

void UManipulationViewComponent::Bind(APawn& InPawn)
{
    if (auto CameraComponent = InPawn.FindComponentByClass<UCameraComponent>())
    {
        if (PostProcessMaterial)
        {
            CameraComponent->PostProcessSettings.AddBlendable(PostProcessMaterial, 1.0f);
        }
    }
}

void UManipulationViewComponent::SelectEntity(AZuruEntity& InEntity)
{
    SelectedEntities.Add(&InEntity);
}

void UManipulationViewComponent::ClearSelection()
{
    SelectedEntities.Reset();
}

void UManipulationViewComponent::BeginPlay()
{
    Super::BeginPlay();

}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION