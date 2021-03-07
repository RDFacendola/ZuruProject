
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "ZuruGizmoComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO COMPONENT                                                 */
/************************************************************************/

// A visual representation of a gizmo on a procedural entity.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS()
class ZURURDF_API UZuruGizmoComponent : public UStaticMeshComponent
{
    GENERATED_BODY()

public:



private:

    UPROPERTY(EditAnywhere, Category = "Gizmo");
    int32 Power;

};


// ==================================================================== //

