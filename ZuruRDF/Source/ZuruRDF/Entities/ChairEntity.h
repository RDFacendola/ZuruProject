
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProceduralMeshComponent.h"

#include "ZuruRDF/Core/ZuruEntity.h"

#include "ChairEntity.generated.h"

// ==================================================================== //

/************************************************************************/
/* CHAIR ENTITY                                                         */
/************************************************************************/

// A procedurally-generated chair.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Chairs)
class ZURURDF_API AChairEntity : public AZuruEntity
{
    GENERATED_BODY()

public:

    // Default constructor.
    AChairEntity();

    // (Re)generate chair geometry.
    void Generate();

    void PostInitProperties() override;

private:

    // Legs' height.
    UPROPERTY(EditAnywhere, Category = Chair)
    float LegsHeight{ 40.0f };

    // Legs' thickness.
    UPROPERTY(EditAnywhere, Category = Chair)
    float LegsThickness{ 3.5f };

    // Seat size, assuming a square shape.
    UPROPERTY(EditAnywhere, Category = Chair)
    float SeatSize{ 40.0f };

    // Seat thickness.
    UPROPERTY(EditAnywhere, Category = Chair)
    float SeatThickness{ 6.0f };

    // Back-seat height from the base.
    UPROPERTY(EditAnywhere, Category = Chair)
    float BackSeatHeight{ 50.0f };

    // Back-seat thickness.
    UPROPERTY(EditAnywhere, Category = Chair)
    float BackSeatThickness{ 3.5f };

    // Back-rest height.
    UPROPERTY(EditAnywhere, Category = Chair)
    float BackRestHeight{ 20.0f };

    // Back-rest height.
    UPROPERTY(EditAnywhere, Category = Chair)
    float BackRestOffset{ 25.0f };

    // Test procedural mesh.
    UPROPERTY(Category = Components, DisplayName = Chair, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
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
