
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
    // Name of the action used to select entities and gizmo in the world.
    static const FName kManipulationSelect;

    // Name of the action used to select additional entities in the world.
    static const FName kManipulationSelectAdditionalEntity;

    // Name of the action used to drag the gizmo forward and backward via mouse movement.
    static const FName kManipulationGizmoDragForward;

    // Name of the action used to drag the gizmo right and left via mouse movement.
    static const FName kManipulationGizmoDragRight;
};

// ==================================================================== //
