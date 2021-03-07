
// ==================================================================== //

#include "ZuruGizmoComponent.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO COMPONENT                                                 */
/************************************************************************/

TOptional<FVector2D> UZuruGizmoComponent::ResolveGizmoTranslation(const FVector2D& InAction) const
{
    return TOptional<FVector2D>{};
}

TOptional<FRotator> UZuruGizmoComponent::ResolveGizmoRotation(const FVector2D& InAction) const
{
    return TOptional<FRotator>{};
}

// ==================================================================== //

