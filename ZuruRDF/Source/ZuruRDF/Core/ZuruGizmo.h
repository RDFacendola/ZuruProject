
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO                                                           */
/************************************************************************/

// Represents a 3D element of user interaction.
// Gizmos are associated to a linear combination of two transforms (named Transform0 and Transform1).
// The interpolation factor (also called "weight") between the two, in zero to one range, determines
// the current gizmo transform and vice-versa.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FZuruGizmo
{
public:

    // Tag to disambiguate function overloads that works with translations.
    struct TranslationTag {};

    // Tag to disambiguate function overloads that works with rotations.
    struct RotationTag {};

    // Tag to disambiguate function overloads that works with scales.
    struct ScaleTag {};

    // Create a new locked gizmo.
    FZuruGizmo();

    // Create a new translation-only gizmo.
    FZuruGizmo(TranslationTag, const FVector& InTranslation0, const FVector& InTranslation1, const FVector& InWeight = FVector{ 0.5f });

    // Create a new rotation-only gizmo.
    // Rotations are expressed in Euler angles to preserve both direction and coiling.
    FZuruGizmo(RotationTag, const FVector& InRotation0, const FVector& InRotation1, const FVector& InWeight = FVector{ 0.5f });

    // Create a new scale-only gizmo.
    FZuruGizmo(ScaleTag, const FVector& InScale0, const FVector& InScale1, const FVector& InWeight = FVector{ 0.5f });

    // Set the translation gizmo weight.
    void SetTranslationWeight(const FVector& InWeight);

    // Set the rotation gizmo weight.
    void SetRotationWeight(const FVector& InWeight);

    // Set the scale gizmo weight.
    void SetScaleWeight(const FVector& InWeight);

    // Get the translation gizmo weight.
    FVector GetTranslationWeight() const;

    // Get the rotation gizmo weight.
    FVector GetRotationWeight() const;

    // Get the scale gizmo weight.
    FVector GetScaleWeight() const;

private:

    // Get a vector-encoded transform given its range and weight.
    FVector GetTransform(const FVector& InBase0, const FVector& InBase1, const FVector& InWeight) const;

    // Get a vector-encoded weight given its range and current transform.
    FVector GetWeight(const FVector& InBase0, const FVector& InBase1, const FVector& InTransform) const;

    // Base translation 0.
    FVector Translation0{ FVector::ZeroVector };

    // Base translation 1.
    FVector Translation1{ FVector::ZeroVector };

    // Base rotation 0.
    FVector Rotation0{ FVector::ZeroVector };

    // Base rotation 1.
    FVector Rotation1{ FVector::ZeroVector };

    // Base scale 0.
    FVector Scale0{ FVector::ZeroVector };

    // Base scale 1.
    FVector Scale1{ FVector::ZeroVector };

    // Gizmo translation.
    FVector Translation{ FVector::ZeroVector };

    // Gizmo rotation.
    // Rotations are expressed in Euler angles to preserve both direction and coiling.
    FVector Rotation{ FVector::ZeroVector };

    // Gizmo scale.
    FVector Scale{ FVector::ZeroVector };

};


// ==================================================================== //

