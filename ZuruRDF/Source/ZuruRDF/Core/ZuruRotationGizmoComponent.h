
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "ZuruGizmoComponent.h"

#include "ZuruRotationGizmoComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* ZURU ROTATION GIZMO COMPONENT                                        */
/************************************************************************/

// A visual representation of a gizmo on a procedural entity.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS()
class ZURURDF_API UZuruRotationGizmoComponent : public UZuruGizmoComponent
{
    GENERATED_BODY()

public:

    virtual TOptional<FRotator> ResolveGizmoRotation(const FVector2D& InGizmoLocation, const FRotator& InGizmoRotation, const FVector2D& InCursorLocation) const;

private:

};


// ==================================================================== //

