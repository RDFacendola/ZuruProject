
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProceduralMeshComponent.h"

#include "ZuruRDF/Core/ZuruEntity.h"

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

    // (Re)generate chair geometry.
    void Generate();

    void PostInitProperties() override;

private:

    // Legs' height.
    UPROPERTY(EditAnywhere, Category = Table)
    float LegsHeight{ 40.0f };

    // Legs' thickness.
    UPROPERTY(EditAnywhere, Category = Table)
    float LegsThickness{ 3.5f };

    // Table-top size, assuming a rectangular shape.
    UPROPERTY(EditAnywhere, Category = Table)
    FVector2D TableTopSize{ 40.0f };

    // Table-top thickness.
    UPROPERTY(EditAnywhere, Category = Table)
    float TableTopThickness{ 6.0f };

    // Test procedural mesh.
    UPROPERTY(Category = Components, DisplayName = Table, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UProceduralMeshComponent* ProceduralComponent{ nullptr };

    // Test material
    UPROPERTY(Category = Components, EditAnywhere)
    UMaterialInterface* Material{ nullptr };

#if WITH_EDITOR

private:

    void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

#endif

};

// ==================================================================== //
