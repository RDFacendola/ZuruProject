
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

    ProceduralComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("TableGeometry"));

    ProceduralComponent->SetupAttachment(GetRootComponent());
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

int32 ATableEntity::GetNumGizmos() const
{
    return 4;
}

FZuruGizmo* ATableEntity::GetGizmo(int32 InIndex)
{
    FZuruGizmo* Gizmos[4] = { &NorthWestGizmo, &NorthEastGizmo, &SouthEastGizmo, &SouthWestGizmo };

    return ((InIndex >= 0) && (InIndex < 4)) ? Gizmos[InIndex] : nullptr;
}

bool ATableEntity::UpdateGizmo(const FZuruGizmo& InGizmo, const FVector2D& InTranslation, const FRotator& InRotation)
{
    if (&InGizmo == &NorthWestGizmo)
    {
        NorthWestGizmo.SetLocation(NorthWestGizmo.GetLocation() + FVector{ InTranslation.X, InTranslation.Y, 0.0f });

        NorthEastGizmo.SetLocation(Crossover(SouthEastGizmo, NorthWestGizmo));
        SouthWestGizmo.SetLocation(Crossover(NorthWestGizmo, SouthEastGizmo));

        return true;
    }

    if (&InGizmo == &NorthEastGizmo)
    {
        NorthEastGizmo.SetLocation(NorthEastGizmo.GetLocation() + FVector{ InTranslation.X, InTranslation.Y, 0.0f });

        NorthWestGizmo.SetLocation(Crossover(SouthWestGizmo, NorthEastGizmo));
        SouthEastGizmo.SetLocation(Crossover(NorthEastGizmo, SouthWestGizmo));

        return true;
    }

    if (&InGizmo == &SouthEastGizmo)
    {
        SouthEastGizmo.SetLocation(SouthEastGizmo.GetLocation() + FVector{ InTranslation.X, InTranslation.Y, 0.0f });

        NorthEastGizmo.SetLocation(Crossover(SouthEastGizmo, NorthWestGizmo));
        SouthWestGizmo.SetLocation(Crossover(NorthWestGizmo, SouthEastGizmo));

        return true;
    }

    if (&InGizmo == &SouthWestGizmo)
    {
        SouthWestGizmo.SetLocation(SouthWestGizmo.GetLocation() + FVector{ InTranslation.X, InTranslation.Y, 0.0f });

        NorthWestGizmo.SetLocation(Crossover(SouthWestGizmo, NorthEastGizmo));
        SouthEastGizmo.SetLocation(Crossover(NorthEastGizmo, SouthWestGizmo));

        return true;
    }

    return false;
}

FVector ATableEntity::Crossover(const FZuruGizmo& InX, const FZuruGizmo& InY) const
{
    return { InX.GetLocation().X, InY.GetLocation().Y, InX.GetLocation().Z };
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
