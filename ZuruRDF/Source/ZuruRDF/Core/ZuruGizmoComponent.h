
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
/* ZURU GIZMO TYPE                                                      */
/************************************************************************/

// Type of a gizmo.
UENUM()
enum class EZuruGizmoType : uint8
{
    // Gizmo affecting translation.
    ZGT_Translation,

    // Gizmo affecting rotation.
    ZGT_Rotation
};

/************************************************************************/
/* ZURU GIZMO COMPONENT                                                 */
/************************************************************************/

// A visual representation of a gizmo on a procedural entity.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Entities)
class ZURURDF_API UZuruGizmoComponent : public UStaticMeshComponent
{
    GENERATED_BODY()

public:

    // Bind this component to a gizmo within an entity.
    void Bind(AZuruEntity& InEntity, int32 InGizmoIndex);

    // Unbind this component from an entity gizmo.
    void Unbind();

    // Synchronize the gizmo component with the actual gizmo within an entity.
    void Synchronize();

    // Whether the gizmo is an entity procedural gizmo.
    bool IsProceduralGizmo();

    // Update a gizmo location within an entity, in world space.
    void ModifyGizmoLocation(const FVector2D& InLocationWS) const;

    // Update a gizmo rotation within an entity, in world space.
    void ModifyGizmoRotation(const FRotator& InRotationWS) const;

    // Set the gizmo type.
    void SetGizmoType(EZuruGizmoType InGizmoType);

    // Get the gizmo type.
    EZuruGizmoType GetGizmoType() const;

private:

    // Whether this gizmo affects translation.
    UPROPERTY(EditAnywhere, Category = Gizmo)
    EZuruGizmoType GizmoType{ EZuruGizmoType::ZGT_Translation };

    // Owning entity.
    AZuruEntity* Entity{ nullptr };

    // Gizmo index.
    int32 GizmoIndex{ -1 };
};


// ==================================================================== //

