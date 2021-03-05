
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL VERTEX                                                    */
/************************************************************************/

// Represents procedurally-generated vertex. POD type.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralVertex
{
    // Vertex position, in local-space world units.
    FVector Position{ FVector::ZeroVector };

    // Vertex normal direction.
    FVector Normal{ FVector::ZeroVector };

    // UV coordinates.
    FVector2D UV{ FVector2D::ZeroVector };
};

// ==================================================================== //
