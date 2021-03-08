
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

void FZuruGizmo::SetLocation(const FVector2D& InLocation)
{
    Location.X = InLocation.X;
    Location.Y = InLocation.Y;
}

void FZuruGizmo::SetHeight(float InHeight)
{
    Location.Z = InHeight;
}

// ==================================================================== //

