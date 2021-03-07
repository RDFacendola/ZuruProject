
// ==================================================================== //

#include "ZuruGizmoComponent.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO COMPONENT                                                 */
/************************************************************************/

FVector2D UZuruGizmoComponent::ResolveGizmoTranslation(const FVector2D& InGizmoLocation, const FRotator& InGizmoRotation, const FVector2D& InCursorLocation) const
{
    return FVector2D::ZeroVector;
}

TOptional<FRotator> UZuruGizmoComponent::ResolveGizmoRotation(const FVector2D& InGizmoLocation, const FRotator& InGizmoRotation, const FVector2D& InCursorLocation) const
{
    return TOptional<FRotator>{};
}

// ==================================================================== //

