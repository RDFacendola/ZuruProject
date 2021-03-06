
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

/************************************************************************/
/* CHAIR ENTITY                                                         */
/************************************************************************/

AChairEntity::AChairEntity()
{
    // Root component.

    ProceduralComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Root"));

    SetRootComponent(ProceduralComponent);
}

void AChairEntity::BeginPlay()
{
    Super::BeginPlay();
    
    auto ProceduralMeshBuilder = FProceduralGeometryBuilder{};

    // Legs.

    ProceduralMeshBuilder << FProceduralMirror{ FVector::RightVector }
                          << FProceduralMirror{ FVector::ForwardVector }
                          << FProceduralExtrude{ FVector::UpVector * 45.0f }
                          << FProceduralTranslate{ { 25.0f, 25.0f } }
                          << FProceduralCircle{ { 5.0f, 5.0f } };

    // Base.

    ProceduralMeshBuilder << FProceduralExtrude{ FVector::UpVector * 5.0f }
                          << FProceduralTranslate{ FVector::UpVector * 45.0f }
                          << FProceduralQuad{ { 60.0f, 60.0f } };

    // Backseat.

    ProceduralMeshBuilder << FProceduralMirror{ FVector::RightVector }
                          << FProceduralExtrude{ FVector::UpVector * 100.0f }
                          << FProceduralTranslate{ FVector::BackwardVector * 25.0f + FVector::UpVector * 45.0f + FVector::RightVector * 25.0f }
                          << FProceduralCircle{ { 5.0f, 5.0f } };

    // Prefab.

    auto Prefab = ProceduralMeshBuilder.Build();

    // Generate.

    ProceduralComponent->ClearAllMeshSections();
    
    Prefab.Generate(*ProceduralComponent, 0);

    ProceduralComponent->SetMaterial(0, Material);
}

// ==================================================================== //

