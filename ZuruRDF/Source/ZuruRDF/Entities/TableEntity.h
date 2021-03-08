
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProceduralMeshComponent.h"

#include "ZuruRDF/Core/ZuruEntity.h"
#include "ChairEntity.h"

#include "TableEntity.generated.h"

// ==================================================================== //

/************************************************************************/
/* TABLE ENTITY                                                         */
/************************************************************************/

// A procedurally-generated table.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Tables)
class ZURURDF_API ATableEntity : public AZuruEntity
{
    GENERATED_BODY()

public:

    // Default constructor.
    ATableEntity();

    virtual void Generate() override;

    // Generate chairs.
    void GenerateChairs();

    void PostInitProperties() override;

    virtual int32 GetNumGizmos() const override;

    virtual FZuruGizmo* GetGizmo(int32 InIndex) override;

    virtual void SetGizmoLocation(int32 InGizmoIndex, const FVector2D& InLocationWS) override;

private:

    // Generate or recycle a new chair.
    AChairEntity* SpawnChair();
    
    // Collect all chairs spawned so far.
    void CollectChairs();

    // Spawn a row chair.
    void SpawnChairRow(const FVector2D& InStartLS, const FVector2D& InEndLS, const FRotator& InRotationLS, float InSpacing, TArray<AChairEntity*>& OutChairs);

    // Legs' height.
    UPROPERTY(EditAnywhere, Category = Table)
    float LegsHeight{ 40.0f };

    // Legs' thickness.
    UPROPERTY(EditAnywhere, Category = Table)
    float LegsThickness{ 3.5f };

    // Table-top thickness.
    UPROPERTY(EditAnywhere, Category = Table)
    float TableTopThickness{ 6.0f };

    // Maximum table size.
    UPROPERTY(EditAnywhere, Category = Table)
    FVector2D MaxSize{ 100.0f, 100.0f };

    // Minimum table size.
    UPROPERTY(EditAnywhere, Category = Table)
    FVector2D MinSize{ 500.0f, 500.0f };

    // Chair spacing, in world units.
    UPROPERTY(EditAnywhere, Category = Table)
    float ChairSpacing{ 50.0f };

    // Concrete chair class type.
    UPROPERTY(EditAnywhere, Category = Table)
    TSubclassOf<AChairEntity> ChairEntityClass{ AChairEntity::StaticClass() };

    // Test procedural mesh.
    UPROPERTY(Category = Components, DisplayName = Table, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UProceduralMeshComponent* ProceduralComponent{ nullptr };

    // Test material
    UPROPERTY(Category = Components, EditAnywhere)
    UMaterialInterface* Material{ nullptr };

    // North-west corner gizmo.
    FZuruGizmo NorthWestGizmo{ FVector{ +50.0f, -50.0f, 50.0f } };

    // North-east corner gizmo.
    FZuruGizmo NorthEastGizmo{ FVector{ +50.0f, +50.0f, 50.0f } };

    // South-west corner gizmo.
    FZuruGizmo SouthEastGizmo{ FVector{ -50.0f, +50.0f, 50.0f } };

    // South-east corner gizmo.
    FZuruGizmo SouthWestGizmo{ FVector{ -50.0f, -50.0f, 50.0f } };

    // North chair row.
    UPROPERTY()
    TArray<AChairEntity*> NorthChairs;

    // East chair row.
    UPROPERTY()
    TArray<AChairEntity*> EastChairs;

    // South chair row.
    UPROPERTY()
    TArray<AChairEntity*> SouthChairs;

    // West chair row.
    UPROPERTY()
    TArray<AChairEntity*> WestChairs;

    // Pool of chairs ready to be recycled.
    UPROPERTY()
    TArray<AChairEntity*> ChairPool;

#if WITH_EDITOR

private:

    void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

};

// ==================================================================== //
