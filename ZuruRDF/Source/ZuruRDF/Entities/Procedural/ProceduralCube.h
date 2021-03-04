
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Math/Vector.h"

#include "ProceduralMesh.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL CUBE                                                      */
/************************************************************************/

// Represents a procedurally-generated cube.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralCube : public FProceduralMesh
{
public:

    // Create a new cube by size, in world units.
    FProceduralCube(float InDepth, float InWidth, float InHeight);

    // Create a new cube by size, in world units.
    FProceduralCube(const FVector& InSize);

    // Default copy constructor.
    FProceduralCube(const FProceduralCube& InRHS) = default;

    // Default copy-assignment operator.
    FProceduralCube& operator=(const FProceduralCube& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralCube() = default;

private:

    virtual void Build(FProceduralGeometryStream& OutGeometryStream) const override;

    // Size of the cube, in world units.
    FVector Size{ FVector::ZeroVector };

};

// ==================================================================== //
