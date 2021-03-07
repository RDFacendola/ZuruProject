
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "ZuruGizmoComponent.h"

#include "ZuruTranslationGizmoComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* ZURU TRANSLATION GIZMO COMPONENT                                     */
/************************************************************************/

// A visual representation of a translation-only gizmo on a procedural entity.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS()
class ZURURDF_API UZuruTranslationGizmoComponent : public UZuruGizmoComponent
{
    GENERATED_BODY()

public:

    virtual TOptional<FVector2D> ResolveGizmoTranslation(const FVector2D& InAction) const override;

private:

};


// ==================================================================== //

