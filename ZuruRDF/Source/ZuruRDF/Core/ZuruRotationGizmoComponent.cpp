
// ==================================================================== //

#include "ZuruRotationGizmoComponent.h"

// ==================================================================== //

/************************************************************************/
/* ZURU ROTATION GIZMO COMPONENT                                        */
/************************************************************************/

TOptional<FRotator> UZuruRotationGizmoComponent::ResolveGizmoRotation(const FVector2D& InGizmoLocation, const FRotator& InGizmoRotation, const FVector2D& InCursorLocation) const
{
    auto GizmoLocation = FVector{ InGizmoLocation.X, InGizmoLocation.Y, 0.0f };
    auto CursorLocation = FVector{ InCursorLocation.X, InCursorLocation.Y, 0.0f };

    return FRotationMatrix::MakeFromX(CursorLocation - GizmoLocation).Rotator();
}

// ==================================================================== //

