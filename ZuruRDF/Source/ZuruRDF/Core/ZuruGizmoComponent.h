
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

    // Bind this component to an entity gizmo.
    void Bind(const FZuruGizmo& InGizmo);

    // Unbind this component from an entity gizmo.
    void Unbind();

    // Rebind the component with the underlying gizmo, updating its status.
    void Rebind();

    // Get the gizmo bound to this come.
    const FZuruGizmo* GetEntityGizmo() const;

    // Evaluate gizmo translation relative to the current cursor position, in world space.
    FVector2D ResolveGizmoTranslation(const FVector2D& InCursorLocation) const;

    // Evaluate gizmo rotation action relative to the current cursor position, in world space.
    FRotator ResolveGizmoRotation(const FVector2D& InCursorLocation) const;

    // Set the gizmo type.
    void SetGizmoType(EZuruGizmoType InGizmoType);

    // Get the gizmo type.
    EZuruGizmoType GetGizmoType() const;

private:

    // Whether this gizmo affects translation.
    UPROPERTY(EditAnywhere, Category = Gizmo)
    EZuruGizmoType GizmoType{ EZuruGizmoType::ZGT_Translation };

    // Entity gizmo.
    const FZuruGizmo* Gizmo{ nullptr };
};


// ==================================================================== //
