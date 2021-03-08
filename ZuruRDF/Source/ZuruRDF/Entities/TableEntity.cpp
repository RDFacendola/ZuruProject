
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

        // Add chairs.

        auto Flags = GetFlags();
        auto World = GetWorld();
        auto WorldType = World ? World->WorldType : EWorldType::None;

        auto bIsClassDefaultObject = (Flags & EObjectFlags::RF_ClassDefaultObject) != 0;
        auto bIsGameWorld = (WorldType == EWorldType::Game) || (WorldType == EWorldType::PIE);

        if (!bIsClassDefaultObject && bIsGameWorld)
        {
            GenerateChairs();
        }

        // Update gizmos height.

        auto GizmoHeight = LegsHeight + TableTopThickness + 3.0f;

        NorthWestGizmo.SetHeight(GizmoHeight);
        NorthEastGizmo.SetHeight(GizmoHeight);
        SouthEastGizmo.SetHeight(GizmoHeight);
        SouthWestGizmo.SetHeight(GizmoHeight);
    }
}

void ATableEntity::GenerateChairs()
{
    // Generate chairs.

    CollectChairs();

    auto NorthWestLocation = FVector2D{ NorthWestGizmo.GetLocation() };
    auto NorthEastLocation = FVector2D{ NorthEastGizmo.GetLocation() };
    auto SouthEastLocation = FVector2D{ SouthEastGizmo.GetLocation() };
    auto SouthWestLocation = FVector2D{ SouthWestGizmo.GetLocation() };

    SpawnChairRow(NorthWestLocation, NorthEastLocation, FRotator{ 0.0f, -180.0f, 0.0f }, ChairSpacing, NorthChairs);
    SpawnChairRow(NorthEastLocation, SouthEastLocation, FRotator{ 0.0f, -90.0f, 0.0f }, ChairSpacing, EastChairs);
    SpawnChairRow(SouthEastLocation, SouthWestLocation, FRotator{ 0.0f, 0.0f, 0.0f }, ChairSpacing, SouthChairs);
    SpawnChairRow(SouthWestLocation, NorthWestLocation, FRotator{ 0.0f, +90.0f, 0.0f }, ChairSpacing, WestChairs);
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

AChairEntity* ATableEntity::SpawnChair()
{
    AChairEntity* ChairEntity{ nullptr };

    if (ChairPool.Num() > 0)
    {
        // Recycle an old chair.

        ChairEntity = ChairPool.Pop();
    }
    else
    {
        // Spawn a brand new chair.

        auto ConcreteChairEntityClass = ChairEntityClass ? ChairEntityClass : AChairEntity::StaticClass();

        auto SpawnParameters = FActorSpawnParameters{};

        SpawnParameters.bNoFail = true;

        ChairEntity = GetWorld()->SpawnActor<AChairEntity>(ConcreteChairEntityClass, FTransform::Identity, SpawnParameters);

        ChairEntity->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
    }

    ChairEntity->SetActorHiddenInGame(false);

    return ChairEntity;
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

    auto MinBoundaryLS = FVector2D{ GetGizmo(OpposingIndex)->GetLocation() } +MinSize * OpposingCorner[OpposingIndex];
    auto MaxBoundaryLS = FVector2D{ GetGizmo(OpposingIndex)->GetLocation() } +MaxSize * OpposingCorner[OpposingIndex];

    auto BoundaryLS = FBox2D{};

    BoundaryLS.Min.X = FMath::Min(MinBoundaryLS.X, MaxBoundaryLS.X);
    BoundaryLS.Min.Y = FMath::Min(MinBoundaryLS.Y, MaxBoundaryLS.Y);
    BoundaryLS.Max.X = FMath::Max(MinBoundaryLS.X, MaxBoundaryLS.X);
    BoundaryLS.Max.Y = FMath::Max(MinBoundaryLS.Y, MaxBoundaryLS.Y);

    auto BoundedLocationLS = BoundaryLS.GetClosestPointTo(LocationLS);

    Gizmo->SetLocation(BoundedLocationLS);

    // Recompute other gizmos.

    auto NorthWestLocation = FVector2D{ NorthWestGizmo.GetLocation() };
    auto NorthEastLocation = FVector2D{ NorthEastGizmo.GetLocation() };
    auto SouthEastLocation = FVector2D{ SouthEastGizmo.GetLocation() };
    auto SouthWestLocation = FVector2D{ SouthWestGizmo.GetLocation() };

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

    // Recenter the table relative to its gizmos.

    auto EntitySize = (NorthWestLocation - SouthWestLocation);
    auto EntityCenterLS = (NorthWestLocation + SouthEastLocation) * 0.5f;

    NorthWestLocation -= EntityCenterLS;
    NorthEastLocation -= EntityCenterLS;
    SouthEastLocation -= EntityCenterLS;
    SouthWestLocation -= EntityCenterLS;

    auto EntityCenterWS = GetActorTransform().TransformPosition(FVector{ EntityCenterLS.X, EntityCenterLS.Y, 0.0f });

    auto TableLocation = GetActorLocation();

    TableLocation.X = EntityCenterWS.X;
    TableLocation.Y = EntityCenterWS.Y;

    SetActorLocation(TableLocation);

    // Update gizmos.

    NorthWestGizmo.SetLocation(NorthWestLocation);
    NorthEastGizmo.SetLocation(NorthEastLocation);
    SouthEastGizmo.SetLocation(SouthEastLocation);
    SouthWestGizmo.SetLocation(SouthWestLocation);

    // #TODO This is horribly inefficient. Legs geometry can be cached, also without a proper
    //       hidden surface strategy we end up generating a tons of triangles.

    Generate();
}

void ATableEntity::CollectChairs()
{
    ChairPool.Append(NorthChairs);
    ChairPool.Append(EastChairs);
    ChairPool.Append(SouthChairs);
    ChairPool.Append(WestChairs);

    NorthChairs.Reset();
    EastChairs.Reset();
    SouthChairs.Reset();
    WestChairs.Reset();

    for (auto&& Chair : ChairPool)
    {
        Chair->SetActorHiddenInGame(true);
    }
}

void ATableEntity::SpawnChairRow(const FVector2D& InStartLS, const FVector2D& InEndLS, const FRotator& InRotationLS, float InSpacing, TArray<AChairEntity*>& OutChairs)
{
    auto Direction = (InEndLS - InStartLS).GetSafeNormal();

    auto ChairStartLS = InStartLS + Direction * InSpacing * 0.5f;
    auto ChairEndLS = InEndLS - Direction * InSpacing * 0.5f;

    auto Distance = (ChairEndLS - ChairStartLS).Size();

    auto ChairsToSpawn = FMath::FloorToInt(Distance / InSpacing);

    auto TableToWorldTransform = GetActorTransform();

    for (auto ChairIndex = 0; ChairIndex < ChairsToSpawn; ++ChairIndex)
    {
        auto Chair = SpawnChair();

        auto Blend = (ChairIndex + 0.5f) / ChairsToSpawn;

        auto ChairPositionLS = FMath::Lerp(ChairStartLS, ChairEndLS, Blend);

        auto ChairPositionWS = TableToWorldTransform.TransformPosition(FVector{ ChairPositionLS.X, ChairPositionLS.Y, 0.0f });
        auto ChairRotationWS = TableToWorldTransform.TransformRotation(FQuat{ InRotationLS });

        Chair->SetActorLocationAndRotation(ChairPositionWS, ChairRotationWS);

        OutChairs.Emplace(Chair);
    }
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
