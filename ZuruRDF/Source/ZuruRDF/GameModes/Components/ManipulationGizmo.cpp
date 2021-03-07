
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

    TranslateGizmoComponent = CreateDefaultSubobject<UZuruTranslationGizmoComponent>(TEXT("GizmoTranslate"));

    TranslateGizmoComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    TranslateGizmoComponent->SetCastShadow(false);

    TranslateGizmoComponent->SetupAttachment(GizmoRoot);

    // Rotate gizmo.

    RotateGizmoComponent = CreateDefaultSubobject<UZuruRotationGizmoComponent>(TEXT("GizmoRotate"));

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
    GizmoActions.AbsolutePosition = TOptional<FVector2D>{};
    GizmoActions.AbsoluteRotation = TOptional<FRotator>{};

    bDragAxisConsume = true;
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

        SetActorLocation(GizmoLocation + FVector::UpVector, false, nullptr, ETeleportType::ResetPhysics);
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
            GizmoActions.ActiveGizmo = Cast<UZuruGizmoComponent>(HitResult.GetComponent());

            OriginalGizmoLocation = FVector2D{ HitResult.GetComponent()->GetComponentLocation() };
            OriginalGizmoRotation = HitResult.GetComponent()->GetComponentRotation();
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
    InInputComponent.BindAxis(FManipulationInputs::kManipulationGizmoDragForward, this, &AManipulationGizmo::OnDragAxis);
    InInputComponent.BindAxis(FManipulationInputs::kManipulationGizmoDragRight, this, &AManipulationGizmo::OnDragAxis);
}

void AManipulationGizmo::OnDragAxis(float InValue)
{
    if (bDragAxisConsume && GizmoActions.ActiveGizmo)
    {
        bDragAxisConsume = false;

        auto HitResult = FHitResult{};

        if (PlayerController->GetHitResultUnderCursorForObjects({ FloorObjectType }, false, HitResult))
        {
            auto CursorLocation = FVector2D{ HitResult.ImpactPoint };

            // Detect gizmo actions based on the cursor position.

            GizmoActions.Translation = GizmoActions.ActiveGizmo->ResolveGizmoTranslation(OriginalGizmoLocation, OriginalGizmoRotation, CursorLocation);

            // Update the gizmo itself to reflect the actions.

            auto ActiveGizmo = (GizmoActions.ActiveGizmo == TranslateGizmoComponent || GizmoActions.ActiveGizmo == RotateGizmoComponent) ? GetRootComponent() : GizmoActions.ActiveGizmo;

            auto ActiveGizmoLocation = ActiveGizmo->GetComponentLocation();
            auto ActiveGizmoTranslation = FVector{ GizmoActions.Translation.X, GizmoActions.Translation.Y, 0.0f };

            ActiveGizmo->SetWorldLocation(ActiveGizmoLocation + ActiveGizmoTranslation);


            // GizmoActions.AbsoluteRotation = GizmoActions.ActiveGizmo->ResolveGizmoRotation(OriginalGizmoLocation, OriginalGizmoRotation, CursorLocation);
//             if (GizmoActions.AbsoluteRotation.IsSet())
//             {
//                 ActiveGizmo->SetWorldRotation(GizmoActions.AbsoluteRotation.GetValue());
//             }            
        }
    }
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION