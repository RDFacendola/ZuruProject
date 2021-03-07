
// ==================================================================== //

#include "ZuruGizmoComponent.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO COMPONENT                                                 */
/************************************************************************/

PRAGMA_DISABLE_OPTIMIZATION

void UZuruGizmoComponent::Bind(AZuruEntity& InEntity, int32 InGizmoIndex)
{
    Entity = &InEntity;
    GizmoIndex = InGizmoIndex;

    Synchronize();

    SetHiddenInGame(false);
}

void UZuruGizmoComponent::Unbind()
{
    Entity = nullptr;
    GizmoIndex = -1;

    SetHiddenInGame(true);
}

void UZuruGizmoComponent::Synchronize()
{
    if (Entity)
    {
        if (auto Gizmo = Entity->GetGizmo(GizmoIndex))
        {
            auto EntityToWorld = Entity->GetActorTransform();

            auto GizmoLocationLS = Gizmo->GetLocation();
            auto GizmoLocationWS = EntityToWorld.TransformPosition(GizmoLocationLS);

            SetWorldLocation(GizmoLocationWS, false, nullptr, ETeleportType::None);
        }
    }
}

bool UZuruGizmoComponent::IsProceduralGizmo()
{
    return GizmoIndex > -1;
}

void UZuruGizmoComponent::ModifyGizmoLocation(const FVector2D& InLocationWS) const
{
    Entity->SetGizmoLocation(GizmoIndex, InLocationWS);
}

void UZuruGizmoComponent::ModifyGizmoRotation(const FRotator& InRotationWS) const
{
    Entity->SetGizmoRotation(GizmoIndex, InRotationWS);
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

