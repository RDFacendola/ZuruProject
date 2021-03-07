
// ==================================================================== //

#include "ZuruInputs.h"

// ==================================================================== //

bool FZuruInputs::DetectDoubleClick(UWorld& InWorld, float& InOutTimestamp)
{
    auto Timestamp = InWorld.GetRealTimeSeconds();

    if (Timestamp - InOutTimestamp < kDoubleClickInterval)
    {
        // Double click!

        InOutTimestamp = 0.0f;

        return true;
    }
    else
    {
        // Reset the combo.

        InOutTimestamp = Timestamp;

        return false;
    }
}

// ==================================================================== //

