
// ==================================================================== //

#include "ChairEntity.h"

#include "Procedural/ProceduralGeometryBuilder.h"

#include "Procedural/ProceduralQuad.h"
#include "Procedural/ProceduralCircle.h"

#include "Procedural/ProceduralNull.h"
#include "Procedural/ProceduralIdentity.h"
#include "Procedural/ProceduralTranslate.h"
#include "Procedural/ProceduralRotate.h"
#include "Procedural/ProceduralScale.h"
#include "Procedural/ProceduralMirror.h"
#include "Procedural/ProceduralExtrude.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

/************************************************************************/
/* CHAIR ENTITY                                                         */
/************************************************************************/

AChairEntity::AChairEntity()
{
    // Root component.

    ProceduralComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TableGeometry"));
    
    ProceduralComponent->SetupAttachment(GetRootComponent());
}

void AChairEntity::Generate()
{
    if (ProceduralComponent)
    {
        // #TODO Prefabs can be generated once and shared between any number of procedural entities.

        auto ProceduralMeshBuilder = FProceduralGeometryBuilder{};

        // Legs.

        ProceduralMeshBuilder << FProceduralMirror{ FVector::RightVector }
                              << FProceduralMirror{ FVector::ForwardVector }
                              << FProceduralExtrude{ FVector::UpVector * LegsHeight }
                              << FProceduralTranslate{ { SeatSize * 0.5f, SeatSize * 0.5f } }
                              << FProceduralTranslate{ { -LegsThickness * 0.5f, -LegsThickness * 0.5f } }
                              << FProceduralCircle{ { LegsThickness, LegsThickness } };

        // Base.

        ProceduralMeshBuilder << FProceduralExtrude{ FVector::UpVector * SeatThickness }
                              << FProceduralTranslate{ FVector::UpVector * LegsHeight }
                              << FProceduralQuad{ { SeatSize, SeatSize } };

        // Backseat.

        ProceduralMeshBuilder << FProceduralMirror{ FVector::RightVector }
                              << FProceduralExtrude{ FVector::UpVector * BackSeatHeight }
                              << FProceduralTranslate{ FVector::UpVector * LegsHeight }
                              << FProceduralTranslate{ FVector::UpVector * SeatThickness }
                              << FProceduralTranslate{ { -SeatSize * 0.5f, -SeatSize * 0.5f } }
                              << FProceduralTranslate{ { +BackSeatThickness * 0.5f, +BackSeatThickness * 0.5f } }
                              << FProceduralCircle{ { BackSeatThickness, BackSeatThickness } };

        // Backrest.

        ProceduralMeshBuilder << FProceduralTranslate{ FVector::UpVector * LegsHeight }
                              << FProceduralTranslate{ FVector::UpVector * SeatThickness }
                              << FProceduralTranslate{ FVector::UpVector * BackRestOffset }
                              << FProceduralExtrude{ FVector::UpVector * BackRestHeight }
                              << FProceduralTranslate{ FVector::BackwardVector * (SeatSize * 0.5f) }
                              << FProceduralTranslate{ FVector::ForwardVector * (BackSeatThickness * 0.5f) }
                              << FProceduralQuad{ { BackSeatThickness, SeatSize - BackSeatThickness } };

        // Prefab.

        auto Prefab = ProceduralMeshBuilder.Build();

        SetCollisionBounds(Prefab.GetBounds());

        // Generate.

        ProceduralComponent->ClearAllMeshSections();
    
        Prefab.Generate(*ProceduralComponent, 0);

        ProceduralComponent->SetMaterial(0, Material);
    }
}

void AChairEntity::PostInitProperties()
{
    Super::PostInitProperties();

    Generate();
}

#if WITH_EDITOR

void AChairEntity::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    
    Generate();
}

#endif

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //
