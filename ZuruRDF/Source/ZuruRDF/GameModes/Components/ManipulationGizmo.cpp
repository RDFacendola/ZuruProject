
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

    TranslateGizmoComponent->SetCastShadow(false);

    TranslateGizmoComponent->SetupAttachment(GizmoRoot);

    // Rotate gizmo.

    RotateGizmoComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GizmoRotate"));

    RotateGizmoComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    RotateGizmoComponent->SetCastShadow(false);

    RotateGizmoComponent->SetupAttachment(GizmoRoot);

    // Jump-start the gizmo.

    MoveGizmo();
}

void AManipulationGizmo::PostInitProperties()
{
    Super::PostInitProperties();
    
    auto CollisionChannel = UEngineTypes::ConvertToCollisionChannel(GizmoObjectType);

    TranslateGizmoComponent->SetCollisionObjectType(CollisionChannel);
    RotateGizmoComponent->SetCollisionObjectType(CollisionChannel);
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

bool AManipulationGizmo::ConditionalActivateGizmo()
{
    auto HitResult = FHitResult{};

    ActiveGizmoComponent = nullptr;

    if (!IsHidden() && PlayerController->GetHitResultUnderCursorForObjects({ GizmoObjectType }, false, HitResult))
    {
        if ((HitResult.Actor.Get() == this) &&  (HitResult.GetComponent()))
        {
            ActiveGizmoComponent = HitResult.GetComponent();
        }
    }

    return !!ActiveGizmoComponent;
}

void AManipulationGizmo::DeactivateGizmo()
{
    ActiveGizmoComponent = nullptr;
}

void AManipulationGizmo::Bind(APlayerController& InPlayerController)
{
    PlayerController = &InPlayerController;
}

void AManipulationGizmo::Bind(UInputComponent& InInputComponent)
{
    InInputComponent.BindAxis(FManipulationInputs::kManipulationGizmoDragForward, this, &AManipulationGizmo::OnForwardDragAxis);
    InInputComponent.BindAxis(FManipulationInputs::kManipulationGizmoDragRight, this, &AManipulationGizmo::OnRightDragAxis);
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

void AManipulationGizmo::OnForwardDragAxis(float InValue)
{
    if (ActiveGizmoComponent)
    {
        GEngine->AddOnScreenDebugMessage(0x10, 0.0f, FColor::Yellow, TEXT("Dragging gizmo forward"));
    }
}

void AManipulationGizmo::OnRightDragAxis(float InValue)
{
    if (ActiveGizmoComponent)
    {
        GEngine->AddOnScreenDebugMessage(0x11, 0.0f, FColor::Yellow, TEXT("Dragging gizmo right"));
    }
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION