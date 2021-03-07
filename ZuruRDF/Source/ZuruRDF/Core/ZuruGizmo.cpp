
// ==================================================================== //

#include "ZuruGizmo.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO                                                           */
/************************************************************************/

FZuruGizmo::FZuruGizmo(const FVector& InDefaultLocation)
    : DefaultLocation(InDefaultLocation)
    , Location(InDefaultLocation)
{

}

void FZuruGizmo::Reset()
{
    Location = DefaultLocation;
}

const FVector& FZuruGizmo::GetDefaultLocation() const
{
    return DefaultLocation;
}

const FVector& FZuruGizmo::GetLocation() const
{
    return Location;
}

void FZuruGizmo::SetLocation(const FVector& InLocation)
{
    Location = InLocation;
}

// ==================================================================== //

