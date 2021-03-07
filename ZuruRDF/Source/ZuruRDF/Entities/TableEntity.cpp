
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

        auto TableTopSize = FVector2D{ NorthEastGizmo.GetLocation() - SouthWestGizmo.GetLocation() };

        // Legs.

        ProceduralMeshBuilder << FProceduralMirror{ FVector::RightVector }
                              << FProceduralMirror{ FVector::ForwardVector }
                              << FProceduralExtrude{ FVector::UpVector * LegsHeight }
                              << FProceduralTranslate{ TableTopSize * 0.5f }
                              << FProceduralTranslate{ { -LegsThickness * 0.5f, - LegsThickness * 0.5f } }
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
    if ((InIndex >= 0) && (InIndex < 4))
    {
        FZuruGizmo* Gizmos[4] = { &NorthWestGizmo, &NorthEastGizmo, &SouthEastGizmo, &SouthWestGizmo };

        return Gizmos[InIndex];
    }

    return nullptr;
}

void ATableEntity::SetGizmoLocation(int32 InGizmoIndex, const FVector2D& InLocationWS)
{
    auto Gizmo = GetGizmo(InGizmoIndex);

    ensure(Gizmo);

    auto WorldToEntity = GetActorTransform().Inverse();

    auto LocationLS = FVector2D{ WorldToEntity.TransformPosition(FVector{ InLocationWS.X, InLocationWS.Y, 0.0f }) };

    // Limit gizmo according to table size and opposite gizmo location.

    FVector2D OpposingCorner[] =
    {
        FVector2D{ -1.0f, +1.0f },
        FVector2D{ -1.0f, -1.0f },
        FVector2D{ +1.0f, -1.0f },
        FVector2D{ +1.0f, +1.0f }
    };

    auto OpposingIndex = ((InGizmoIndex + 2) % 4);

    auto MinBoundaryLS = FVector2D{ GetGizmo(OpposingIndex)->GetLocation() } + MinSize * OpposingCorner[OpposingIndex];
    auto MaxBoundaryLS = FVector2D{ GetGizmo(OpposingIndex)->GetLocation() } + MaxSize * OpposingCorner[OpposingIndex];

    auto BoundaryLS = FBox2D{};

    BoundaryLS.Min.X = FMath::Min(MinBoundaryLS.X, MaxBoundaryLS.X);
    BoundaryLS.Min.Y = FMath::Min(MinBoundaryLS.Y, MaxBoundaryLS.Y);
    BoundaryLS.Max.X = FMath::Max(MinBoundaryLS.X, MaxBoundaryLS.X);
    BoundaryLS.Max.Y = FMath::Max(MinBoundaryLS.Y, MaxBoundaryLS.Y);

    auto BoundedLocationLS = BoundaryLS.GetClosestPointTo(LocationLS);

    Gizmo->SetLocation(BoundedLocationLS);

    // Recompute other gizmos.

    auto NorthWestLocation = NorthWestGizmo.GetLocation();
    auto NorthEastLocation = NorthEastGizmo.GetLocation();
    auto SouthEastLocation = SouthEastGizmo.GetLocation();
    auto SouthWestLocation = SouthWestGizmo.GetLocation();

    if (InGizmoIndex == 0)
    {
        NorthEastLocation.X = NorthWestLocation.X;
        SouthWestLocation.Y = NorthWestLocation.Y;
    }

    if (InGizmoIndex == 1)
    {
        NorthWestLocation.X = NorthEastLocation.X;
        SouthEastLocation.Y = NorthEastLocation.Y;
    }

    if (InGizmoIndex == 2)
    {
        SouthWestLocation.X = SouthEastLocation.X;
        NorthEastLocation.Y = SouthEastLocation.Y;
    }

    if (InGizmoIndex == 3)
    {
        SouthEastLocation.X = SouthWestLocation.X;
        NorthWestLocation.Y = SouthWestLocation.Y;
    }

    NorthWestGizmo.SetLocation(NorthWestLocation);
    NorthEastGizmo.SetLocation(NorthEastLocation);
    SouthEastGizmo.SetLocation(SouthEastLocation);
    SouthWestGizmo.SetLocation(SouthWestLocation);

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
