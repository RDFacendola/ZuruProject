
// ==================================================================== //

#include "ZuruGizmoComponent.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO COMPONENT                                                 */
/************************************************************************/

PRAGMA_DISABLE_OPTIMIZATION

void UZuruGizmoComponent::Bind(const FZuruGizmo& InGizmo, AZuruEntity& InEntity)
{
    Gizmo = &InGizmo;
    Entity = &InEntity;

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

bool UZuruGizmoComponent::IsProceduralGizmo()
{
    return !!Gizmo;
}

void UZuruGizmoComponent::ModifyGizmoLocation(const FVector2D& InLocation) const
{

}

void UZuruGizmoComponent::ModifyGizmoRotation(const FRotator& InRotation) const
{

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

