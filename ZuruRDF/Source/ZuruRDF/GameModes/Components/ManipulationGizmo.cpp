
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

    TranslateGizmoComponent = CreateDefaultSubobject<UZuruGizmoComponent>(TEXT("GizmoTranslate"));

    TranslateGizmoComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TranslateGizmoComponent->SetCastShadow(false);
    TranslateGizmoComponent->SetGizmoType(EZuruGizmoType::ZGT_Translation);

    TranslateGizmoComponent->SetupAttachment(GizmoRoot);

    // Rotate gizmo.

    RotateGizmoComponent = CreateDefaultSubobject<UZuruGizmoComponent>(TEXT("GizmoRotate"));

    RotateGizmoComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    RotateGizmoComponent->SetCastShadow(false);
    RotateGizmoComponent->SetGizmoType(EZuruGizmoType::ZGT_Rotation);

    RotateGizmoComponent->SetupAttachment(GizmoRoot);

    // Hidden until at least one entity is selected.

    SetActorHiddenInGame(true);
}

void AManipulationGizmo::PostInitProperties()
{
    Super::PostInitProperties();
    
    auto GizmoObjectTypeCollisionChannel = UEngineTypes::ConvertToCollisionChannel(GizmoObjectType);

    TranslateGizmoComponent->SetCollisionObjectType(GizmoObjectTypeCollisionChannel);
    RotateGizmoComponent->SetCollisionObjectType(GizmoObjectTypeCollisionChannel);
}

const FManipulationGizmoActions& AManipulationGizmo::GetActions() const
{
    return GizmoActions;
}

void AManipulationGizmo::ConsumeActions()
{
    GizmoActions.AbsolutePosition = TOptional<FVector2D>{};
    GizmoActions.AbsoluteRotation = TOptional<FRotator>{};

    bDragAxisConsume = true;
}

void AManipulationGizmo::SelectEntities(const TSet<AZuruEntity*>& InSelectedEntities)
{
    SelectedEntities = InSelectedEntities;

    auto bGizmoHidden = (SelectedEntities.Num() == 0);

    SetActorHiddenInGame(bGizmoHidden);

    RetrieveGizmos(InSelectedEntities);
}

void AManipulationGizmo::RetrieveGizmos(const TSet<AZuruEntity*>& InSelectedEntities)
{
    InvalidateGizmos();

    for (auto&& SelectedEntity : InSelectedEntities)
    {
        for (auto GizmoIndex = 0; GizmoIndex < SelectedEntity->GetNumGizmos(); ++GizmoIndex)
        {
            if (auto Gizmo = SelectedEntity->GetGizmo(GizmoIndex))
            {
                auto& GizmoComponent = SpawnProceduralGizmoComponent();

                GizmoComponent.Bind(*Gizmo);
            }
        }
    }
}

UZuruGizmoComponent& AManipulationGizmo::SpawnProceduralGizmoComponent()
{
    UZuruGizmoComponent* GizmoComponent{ nullptr };

    if (ProceduralGizmoComponentPool.Num() > 0)
    {
        // Recycle an old gizmo component.

        GizmoComponent = ProceduralGizmoComponentPool.Pop();
    }
    else
    {
        // Spawn a brand-new gizmo component and set it up.

        auto ConcreteProceduralGizmoComponentClass = ProceduralGizmoComponentClass ? ProceduralGizmoComponentClass : UZuruGizmoComponent::StaticClass();

        GizmoComponent = NewObject<UZuruGizmoComponent>(this, ConcreteProceduralGizmoComponentClass, NAME_None, RF_Transient);
        
        GizmoComponent->RegisterComponent();
        GizmoComponent->AttachToComponent(GizmoRoot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

        auto GizmoObjectTypeCollisionChannel = UEngineTypes::ConvertToCollisionChannel(GizmoObjectType);

        GizmoComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        GizmoComponent->SetCastShadow(false);
        GizmoComponent->SetGizmoType(EZuruGizmoType::ZGT_Translation);
        GizmoComponent->SetCollisionObjectType(GizmoObjectTypeCollisionChannel);
    }

    ProceduralGizmoComponents.Emplace(GizmoComponent);

    return *GizmoComponent;
}

void AManipulationGizmo::InvalidateGizmos()
{
    for (auto&& ProceduralGizmoComponent : ProceduralGizmoComponents)
    {
        ProceduralGizmoComponent->Unbind();
        ProceduralGizmoComponentPool.Emplace(ProceduralGizmoComponent);
    }

    ProceduralGizmoComponents.Reset();
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

            auto GizmoLocation2D = FVector2D{ GizmoActions.ActiveGizmo->GetComponentLocation() };
            auto HitLocation2D = FVector2D{ HitResult.ImpactPoint };

            GizmoBaseRotationForward = (HitLocation2D - GizmoLocation2D).GetSafeNormal();
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

void AManipulationGizmo::Advance(float InDeltaSeconds)
{
    // Update all gizmos.

    for (auto&& ProceduralGizmoComponent : ProceduralGizmoComponents)
    {
        ProceduralGizmoComponent->Rebind();
    }

    // Gizmo translation.

    if (SelectedEntities.Num() > 0)
    {
        auto GizmoLocation = FVector::ZeroVector;

        for (auto&& SelectedEntity : SelectedEntities)
        {
            GizmoLocation += SelectedEntity->GetActorLocation();
        }

        GizmoLocation /= SelectedEntities.Num();

        SetActorLocation(GizmoLocation + FVector::UpVector, false, nullptr, ETeleportType::ResetPhysics);
    }

    // Gizmo rotation.

    if (SelectedEntities.Num() > 0)
    {
        auto GizmoRotation = FRotator::ZeroRotator;

        for (auto&& SelectedEntity : SelectedEntities)
        {
            GizmoRotation = SelectedEntity->GetActorRotation();
            break;
        }

        SetActorRotation(GizmoRotation, ETeleportType::ResetPhysics);
    }
}

void AManipulationGizmo::OnDragAxis(float InValue)
{
    if (bDragAxisConsume && GizmoActions.ActiveGizmo)
    {
        bDragAxisConsume = false;

        auto HitResult = FHitResult{};

        if (PlayerController->GetHitResultUnderCursorForObjects({ FloorObjectType }, false, HitResult))
        {
            auto ActiveGizmoType = GizmoActions.ActiveGizmo->GetGizmoType();

            auto GizmoLocation2D = FVector2D{ GizmoActions.ActiveGizmo->GetComponentLocation() };
            auto HitLocation2D = FVector2D{ HitResult.ImpactPoint };

            if (ActiveGizmoType == EZuruGizmoType::ZGT_Translation)
            {
                GizmoActions.AbsolutePosition = HitLocation2D;
            }

            if (ActiveGizmoType == EZuruGizmoType::ZGT_Rotation)
            {
                auto GizmoRotationForward = (HitLocation2D - GizmoLocation2D).GetSafeNormal();

                auto DeltaRotation = GizmoRotationForward - GizmoBaseRotationForward;

                auto Rotation = FRotationMatrix::MakeFromX(FVector{ DeltaRotation.X, DeltaRotation.Y, 0.0f }).Rotator();

                GizmoActions.AbsoluteRotation = Rotation;
            }
        }
    }
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION