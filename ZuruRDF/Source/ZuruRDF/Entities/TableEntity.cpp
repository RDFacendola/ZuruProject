
// ==================================================================== //

#include "TableEntity.h"

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
/* TABLE ENTITY                                                         */
/************************************************************************/

ATableEntity::ATableEntity()
{
    // Root component.

    ProceduralComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TableRoot"));

    SetRootComponent(ProceduralComponent);
}

void ATableEntity::Generate()
{
    if (ProceduralComponent)
    {
        auto ProceduralMeshBuilder = FProceduralGeometryBuilder{};

        // Legs.

        ProceduralMeshBuilder << FProceduralMirror{ FVector::RightVector }
                              << FProceduralMirror{ FVector::ForwardVector }
                              << FProceduralExtrude{ FVector::UpVector * LegsHeight }
                              << FProceduralTranslate{ TableTopSize * 0.5f }
                              << FProceduralTranslate{ { -LegsThickness * 0.5f, -LegsThickness * 0.5f } }
                              << FProceduralCircle{ { LegsThickness, LegsThickness } };

        // Base.

        ProceduralMeshBuilder << FProceduralExtrude{ FVector::UpVector * TableTopThickness }
                              << FProceduralTranslate{ FVector::UpVector * LegsHeight }
                              << FProceduralQuad{ TableTopSize };

        // Prefab.

        auto Prefab = ProceduralMeshBuilder.Build();

        // Generate.

        ProceduralComponent->ClearAllMeshSections();
    
        Prefab.Generate(*ProceduralComponent, 0);

        ProceduralComponent->SetMaterial(0, Material);
    }
}

void ATableEntity::PostInitProperties()
{
    Super::PostInitProperties();

    Generate();
}

#if WITH_EDITOR

void ATableEntity::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    
    Generate();
}

#endif

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //
