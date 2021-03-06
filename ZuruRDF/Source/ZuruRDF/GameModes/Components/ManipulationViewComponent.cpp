
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
    auto bAlreadySelected = false;

    SelectedEntities.Add(&InEntity, &bAlreadySelected);

    if (!bAlreadySelected)
    {
        SetEntityStencilValue(InEntity, kSelectedEntityCustomDepth);
    }
}

void UManipulationViewComponent::DeselectEntity(AZuruEntity& InEntity)
{
    if(SelectedEntities.Remove(&InEntity) > 0)
    {
        SetEntityStencilValue(InEntity, kDisableCustomStencil);
    }
}

void UManipulationViewComponent::ClearSelection()
{
    for (auto&& SelectedEntity : SelectedEntities)
    {
        SetEntityStencilValue(*SelectedEntity, kDisableCustomStencil);
    }

    SelectedEntities.Reset();
}

void UManipulationViewComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UManipulationViewComponent::SetEntityStencilValue(AZuruEntity& InEntity, int32 InValue)
{
    InEntity.ForEach<UPrimitiveComponent>([InValue](auto& InPrimitiveComponent)
    {
        if (!InPrimitiveComponent.bHiddenInGame)
        {
            InPrimitiveComponent.SetRenderCustomDepth(InValue >= 0);
            InPrimitiveComponent.SetCustomDepthStencilValue(InValue);
            InPrimitiveComponent.MarkRenderStateDirty();
        }
    });
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION