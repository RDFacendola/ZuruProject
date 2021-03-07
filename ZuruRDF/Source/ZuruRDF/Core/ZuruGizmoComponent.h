
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Vector2D.h"
#include "Math/Rotator.h"

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

    virtual TOptional<FVector2D> ResolveGizmoTranslation(const FVector2D& InAction) const;

    virtual TOptional<FRotator> ResolveGizmoRotation(const FVector2D& InAction) const;

private:


};


// ==================================================================== //

