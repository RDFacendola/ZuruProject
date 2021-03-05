
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector2D.h"

#include "ProceduralMesh.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL QUAD                                                      */
/************************************************************************/

// Represents a procedurally-generated quad on the XY plane.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralQuad : public FProceduralMesh
{
public:

    // Create a new quad.
    FProceduralQuad(const FVector2D& InSize);

    // Default copy constructor.
    FProceduralQuad(const FProceduralQuad& InRHS) = default;

    // Default copy-assignment operator.
    FProceduralQuad& operator=(const FProceduralQuad& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralQuad() = default;

private:

    virtual void Build(FProceduralGeometryStream& OutGeometryStream) const override;

    // Size of the quad, in world units.
    FVector Size{ FVector::ZeroVector };

};

// ==================================================================== //
