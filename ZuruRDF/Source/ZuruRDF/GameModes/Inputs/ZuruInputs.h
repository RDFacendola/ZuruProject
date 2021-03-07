
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

// ==================================================================== //

/************************************************************************/
/* ZURU INPUTS                                                          */
/************************************************************************/

// Exposes generic input functions.
//
// @author Raffaele D. Facendola - March 2021.
namespace FZuruInputs
{
    // Minimum time between the same click to register as a "double click".
    constexpr auto kDoubleClickInterval = 0.2f;

    // Check whether a click event is registered as a "double click".
    bool DetectDoubleClick(UWorld& InWorld, float& InOutTimestamp);

};

// ==================================================================== //
