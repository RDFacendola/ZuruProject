
// ==================================================================== //

#include "ProceduralVertex.h"

// ==================================================================== //

/************************************************************************/
/* NON-MEMBER FUNCTIONS                                                 */
/************************************************************************/

FProceduralVertex operator+(const FProceduralVertex& InLHS, const FVector& InRHS)
{
    return
    {
        InLHS.Position + InRHS,
        InLHS.Normal,
        InLHS.UV
    };
}

FProceduralVertex operator-(const FProceduralVertex& InLHS, const FVector& InRHS)
{
    return
    {
        InLHS.Position - InRHS,
        InLHS.Normal,
        InLHS.UV
    };
}

FProceduralVertex operator*(const FProceduralVertex& InLHS, const FVector& InRHS)
{
    // Normal transform should be done by means of the transpose of the inverse of the
    // roto-translation 3x3 sub-matrix, ignoring any translation contributions.
    // Since we have no rotation and scale matrix are diagonal, this boils down to a
    // scaling factor which is the reciprocal of the desired scale.

    return
    {
        InLHS.Position * InRHS,
        (InLHS.Normal / InRHS).GetSafeNormal(),
        InLHS.UV
    };
}

FProceduralVertex operator*(const FProceduralVertex& InLHS, const FRotator& InRHS)
{
    return
    {
        InRHS.RotateVector(InLHS.Position),
        InRHS.RotateVector(InLHS.Normal),
        InLHS.UV
    };
}

// ==================================================================== //
