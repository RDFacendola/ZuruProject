
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

    SelectEntities({});
}

void AManipulationGizmo::PostInitProperties()
{
    Super::PostInitProperties();
    
    auto CollisionChannel = UEngineTypes::ConvertToCollisionChannel(GizmoObjectType);

    TranslateGizmoComponent->SetCollisionObjectType(CollisionChannel);
    RotateGizmoComponent->SetCollisionObjectType(CollisionChannel);
}

const FManipulationGizmoActions& AManipulationGizmo::GetActions() const
{
    return GizmoActions;
}

void AManipulationGizmo::ConsumeActions()
{
    GizmoActions.Translation = FVector2D::ZeroVector;
    GizmoActions.Rotation = FRotator::ZeroRotator;
}

void AManipulationGizmo::SelectEntities(const TSet<AZuruEntity*>& InSelectedEntities)
{
    if (InSelectedEntities.Num() == 0)
    {
        SetActorHiddenInGame(true);
    }
    else
    {
        SetActorHiddenInGame(false);

        auto GizmoLocation = FVector::ZeroVector;

        for (auto&& SelectedEntity : InSelectedEntities)
        {
            GizmoLocation += SelectedEntity->GetActorLocation();
        }

        GizmoLocation /= InSelectedEntities.Num();

        SetActorLocation(GizmoLocation + FVector::UpVector);
    }

    // #TODO Show custom gizmos.
}

bool AManipulationGizmo::ConditionalActivateGizmo()
{
    auto HitResult = FHitResult{};

    GizmoActions.ActiveGizmo = nullptr;

    if (!IsHidden() && PlayerController->GetHitResultUnderCursorForObjects({ GizmoObjectType }, false, HitResult))
    {
        if (HitResult.Actor.Get() == this)
        {
            GizmoActions.ActiveGizmo = Cast<UStaticMeshComponent>(HitResult.GetComponent());
        }
    }

    return !!GizmoActions.ActiveGizmo;
}

void AManipulationGizmo::DeactivateGizmo()
{
    GizmoActions.ActiveGizmo = nullptr;
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

void AManipulationGizmo::OnForwardDragAxis(float InValue)
{
    if (GizmoActions.ActiveGizmo)
    {
        
    }
}

void AManipulationGizmo::OnRightDragAxis(float InValue)
{
    if (GizmoActions.ActiveGizmo)
    {
        
    }
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION