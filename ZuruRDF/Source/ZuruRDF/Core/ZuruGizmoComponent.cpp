
// ==================================================================== //

#include "ZuruGizmoComponent.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO COMPONENT                                                 */
/************************************************************************/

PRAGMA_DISABLE_OPTIMIZATION

void UZuruGizmoComponent::Bind(const FZuruGizmo& InGizmo)
{
    Gizmo = &InGizmo;

    Rebind();

    SetHiddenInGame(false);
}

void UZuruGizmoComponent::Unbind()
{
    Gizmo = nullptr;

    SetHiddenInGame(true);
}

void UZuruGizmoComponent::Rebind()
{
    if (Gizmo)
    {
        auto WorldLocation = GetOwner()->GetActorTransform().TransformPosition(Gizmo->GetLocation());

        SetWorldLocation(WorldLocation, false, nullptr, ETeleportType::None);
    }
}

const FZuruGizmo* UZuruGizmoComponent::GetEntityGizmo() const
{
    return Gizmo;
}

FVector2D UZuruGizmoComponent::ResolveGizmoTranslation(const FVector2D& InCursorLocation) const
{
    auto Translation = InCursorLocation - FVector2D{ GetComponentLocation() };

    return (GizmoType == EZuruGizmoType::ZGT_Translation) ? (Translation) : (FVector2D::ZeroVector);
}

FRotator UZuruGizmoComponent::ResolveGizmoRotation(const FVector2D& InCursorLocation) const
{
    auto GizmoRotation = GetComponentRotation();
    auto GizmoLocation = GetComponentLocation();
    auto CursorLocation = FVector{ InCursorLocation.X, InCursorLocation.Y, 0.0f };

    auto CursorDirection = GizmoRotation.UnrotateVector(CursorLocation).GetSafeNormal2D();

    auto Rotation = FRotationMatrix::MakeFromX(CursorDirection).Rotator();

    return (GizmoType == EZuruGizmoType::ZGT_Rotation) ? (Rotation) : (FRotator::ZeroRotator);
}

void UZuruGizmoComponent::SetGizmoType(EZuruGizmoType InGizmoType)
{
    GizmoType = InGizmoType;
}

EZuruGizmoType UZuruGizmoComponent::GetGizmoType() const
{
    return GizmoType;
}

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //

