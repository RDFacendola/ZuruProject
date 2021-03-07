
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
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FZuruGizmo
{

public:

    // Create a new gizmo
    FZuruGizmo() = default;

    // Create a new gizmo.
    FZuruGizmo(const FVector& InDefaultLocation);

    // Reset the gizmo to its default values.
    void Reset();

    // Get the default gizmo location, in actor space.
    const FVector& GetDefaultLocation() const;

    // Get the gizmo location, in actor space.
    const FVector& GetLocation() const;

    // Set the gizmo location, in actor space.
    void SetLocation(const FVector& InLocation);

private:

    // Default gizmo location.
    FVector DefaultLocation{ FVector::ZeroVector };

    // Current gizmo location.
    FVector Location{ FVector::ZeroVector };

};


// ==================================================================== //

