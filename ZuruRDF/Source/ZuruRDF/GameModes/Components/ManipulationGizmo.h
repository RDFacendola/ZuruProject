
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "ZuruRDF/Core/ZuruGizmo.h"
#include "ZuruRDF/Core/ZuruEntity.h"

#include "ManipulationGizmo.generated.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION GIZMO                                                   */
/************************************************************************/

// Actor used to display 3D gizmo control over an entity being manipulated.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Entites)
class ZURURDF_API AManipulationGizmo : public AActor
{
    GENERATED_BODY()
    
public:

    // Create a new entity.
    AManipulationGizmo();

protected:

private:

    // Gizmo root component.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    USceneComponent* GizmoRoot{ nullptr };

    // Gizmo used to translate the entity..
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* TranslateGizmoComponent{ nullptr };

    // Gizmo used to rotate the entity.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* RotateGizmoComponent { nullptr };

};

// ==================================================================== //

