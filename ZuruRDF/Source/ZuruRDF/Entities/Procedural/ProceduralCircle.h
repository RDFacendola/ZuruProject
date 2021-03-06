
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector2D.h"

#include "ProceduralMesh.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL CIRCLE                                                    */
/************************************************************************/

// Represents a procedurally-generated circle on the XY plane.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralCircle : public FProceduralMesh
{
public:

    // Create a new quad.
    FProceduralCircle(const FVector2D& InDiameter, int32 InTessellation = 16);

    // Default copy constructor.
    FProceduralCircle(const FProceduralCircle& InRHS) = default;

    // Default copy-assignment operator.
    FProceduralCircle& operator=(const FProceduralCircle& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralCircle() = default;

private:

    virtual void Build(FProceduralGeometryStream& OutGeometryStream) const override;

    // Diameter of the circle, in world units.
    FVector Diameter{ FVector::ZeroVector };

    // Tessellation factors affecting the number of sides generated.
    int32 Tessellation{ 16 };

};

// ==================================================================== //
