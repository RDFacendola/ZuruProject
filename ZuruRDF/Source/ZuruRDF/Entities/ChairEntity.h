
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

// Represents a physical object in the project.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Chairs)
class ZURURDF_API AChairEntity : public AZuruEntity
{
    GENERATED_BODY()

public:

    // Default constructor.
    AChairEntity();

    void BeginPlay() override;

private:

    // Test procedural mesh.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UProceduralMeshComponent* ProceduralComponent{ nullptr };

    // Test material
    UPROPERTY(Category = Components, EditAnywhere)
    UMaterialInterface* Material{ nullptr };

};

// ==================================================================== //
