
// ==================================================================== //

#include "ManipulationGizmo.h"

#include "ZuruRDF/GameModes/Inputs/ManipulationInputs.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

/************************************************************************/
/* MANIPULATION GIZMO                                                   */
/************************************************************************/

AManipulationGizmo::AManipulationGizmo()
{
    // Root component.

    GizmoRoot = CreateDefaultSubobject<USceneComponent>(TEXT("GizmoRoot"));

    SetRootComponent(GizmoRoot);

    // Translate gizmo.

    TranslateGizmoComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GizmoTranslate"));

    TranslateGizmoComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TranslateGizmoComponent->SetCollisionObjectType(ECC_GameTraceChannel3);
    TranslateGizmoComponent->SetCastShadow(false);

    TranslateGizmoComponent->SetupAttachment(GizmoRoot);

    // Rotate gizmo.

    RotateGizmoComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GizmoRotate"));

    RotateGizmoComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    RotateGizmoComponent->SetCollisionObjectType(ECC_GameTraceChannel3);
    RotateGizmoComponent->SetCastShadow(false);

    RotateGizmoComponent->SetupAttachment(GizmoRoot);

    // Jump-start the gizmo.

    MoveGizmo();
}

void AManipulationGizmo::SelectEntity(AZuruEntity& InEntity)
{
    SelectedEntities.Add(&InEntity);

    MoveGizmo();
}

void AManipulationGizmo::DeselectEntity(AZuruEntity& InEntity)
{
    SelectedEntities.Remove(&InEntity);

    MoveGizmo();
}

void AManipulationGizmo::ClearSelection()
{
    SelectedEntities.Reset();

    MoveGizmo();
}

void AManipulationGizmo::Bind(APlayerController& InPlayerController)
{
    PlayerController = &InPlayerController;
}

void AManipulationGizmo::Bind(UInputComponent& InInputComponent)
{
    InInputComponent.BindAxis(FManipulationInputs::kGizmoDragForward, this, &AManipulationGizmo::OnForwardDragAxis);
    InInputComponent.BindAxis(FManipulationInputs::kGizmoDragRight, this, &AManipulationGizmo::OnRightDragAxis);

    InInputComponent.BindAction(FManipulationInputs::kGizmoDragEnabled, IE_Pressed, this, &AManipulationGizmo::OnDragGizmoPressed);
    InInputComponent.BindAction(FManipulationInputs::kGizmoDragEnabled, IE_Released, this, &AManipulationGizmo::OnDragGizmoReleased);
}

void AManipulationGizmo::MoveGizmo()
{
    if (SelectedEntities.Num() == 0)
    {
         SetActorHiddenInGame(true);
    }
    else
    {
        SetActorHiddenInGame(false);

        auto GizmoLocation = FVector::ZeroVector;

        for (auto&& SelectedEntity : SelectedEntities)
        {
            GizmoLocation += SelectedEntity->GetActorLocation();
        }

        GizmoLocation /= SelectedEntities.Num();

        SetActorLocation(GizmoLocation + FVector::UpVector);
    }
}

void AManipulationGizmo::OnDragGizmoPressed()
{
    bDragEnabled = true;
}

void AManipulationGizmo::OnDragGizmoReleased()
{
    bDragEnabled = false;
}

void AManipulationGizmo::OnForwardDragAxis(float InValue)
{
    if (bDragEnabled)
    {

    }
}

void AManipulationGizmo::OnRightDragAxis(float InValue)
{
    if (bDragEnabled)
    {

    }
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION