
// ==================================================================== //

#include "ZuruTranslationGizmoComponent.h"

// ==================================================================== //

/************************************************************************/
/* ZURU TRANSLATION GIZMO COMPONENT                                     */
/************************************************************************/

FVector2D UZuruTranslationGizmoComponent::ResolveGizmoTranslation(const FVector2D& InGizmoLocation, const FRotator& InGizmoRotation, const FVector2D& InCursorLocation) const
{
    return InCursorLocation - FVector2D{ GetComponentLocation() };
}

// ==================================================================== //

