
// ==================================================================== //

#include "ManipulationWidget.h"

#include "Camera/CameraComponent.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

/************************************************************************/
/* MANIPULATION WIDGET                                                  */
/************************************************************************/

void UManipulationWidget::Bind(APlayerController& InPlayerController)
{
    AddToViewport();
}

void UManipulationWidget::Bind(APawn& InPawn)
{
    if (auto CameraComponent = InPawn.FindComponentByClass<UCameraComponent>())
    {
        if (PostProcessMaterial)
        {
            CameraComponent->PostProcessSettings.AddBlendable(PostProcessMaterial, 1.0f);
        }
    }
}

void UManipulationWidget::SelectEntity(AZuruEntity& InEntity)
{
    auto bAlreadySelected = false;

    SelectedEntities.Add(&InEntity, &bAlreadySelected);

    if (!bAlreadySelected)
    {
        SetEntityStencilValue(InEntity, kSelectedEntityCustomDepth);
    }
}

void UManipulationWidget::DeselectEntity(AZuruEntity& InEntity)
{
    if(SelectedEntities.Remove(&InEntity) > 0)
    {
        SetEntityStencilValue(InEntity, kDisableCustomStencil);
    }
}

void UManipulationWidget::ClearSelection()
{
    for (auto&& SelectedEntity : SelectedEntities)
    {
        SetEntityStencilValue(*SelectedEntity, kDisableCustomStencil);
    }

    SelectedEntities.Reset();
}

void UManipulationWidget::SetEntityStencilValue(AZuruEntity& InEntity, int32 InValue)
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