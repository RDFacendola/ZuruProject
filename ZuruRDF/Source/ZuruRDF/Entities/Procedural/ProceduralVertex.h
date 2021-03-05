
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

/************************************************************************/
/* NON-MEMBER FUNCTIONS                                                 */
/************************************************************************/

// Add an offset to a vertex position.
FProceduralVertex operator+(const FProceduralVertex& InLHS, const FVector& InRHS);

// Subtract an offset to a vertex position.
FProceduralVertex operator-(const FProceduralVertex& InLHS, const FVector& InRHS);

// Scale a vertex position and normal.
FProceduralVertex operator*(const FProceduralVertex& InLHS, const FVector& InRHS);

// Rotate a vertex position and normal.
FProceduralVertex operator*(const FProceduralVertex& InLHS, const FRotator& InRHS);

// ==================================================================== //
