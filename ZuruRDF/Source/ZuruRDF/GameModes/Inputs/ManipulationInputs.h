
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE INPUTS                                                      */
/************************************************************************/

// Exposes manipulation-relevant inputs.
//
// @author Raffaele D. Facendola - February 2021.
struct ZURURDF_API FManipulationInputs
{
    // Name of the action used to select entities in the world.
    static const FName kSelectEntity;

    // Name of the action used to select additional entities in the world.
    static const FName kSelectAdditionalEntity;
};

// ==================================================================== //
