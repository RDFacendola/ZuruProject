
// ==================================================================== //

#include "ManipulationGizmo.h"

// ==================================================================== //

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
    TranslateGizmoComponent->SetCollisionObjectType(ECC_GameTraceChannel3);
    TranslateGizmoComponent->SetCastShadow(false);

    TranslateGizmoComponent->SetupAttachment(GizmoRoot);

    // Rotate gizmo.

    RotateGizmoComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GizmoRotate"));

    RotateGizmoComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    RotateGizmoComponent->SetCollisionObjectType(ECC_GameTraceChannel3);
    RotateGizmoComponent->SetCastShadow(false);

    RotateGizmoComponent->SetupAttachment(GizmoRoot);

}

// ==================================================================== //

