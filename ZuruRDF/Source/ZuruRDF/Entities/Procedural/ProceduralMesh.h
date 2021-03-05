
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"

#include "ProceduralGeometryStream.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY MESH                                             */
/************************************************************************/

// Base interface for procedurally-generated meshes.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralMesh
{
public:

    // Default virtual destructor.
    virtual ~FProceduralMesh() = default;

    // Append a procedurally-generated geometry to a geometry stream.
    void AppendTo(FProceduralGeometryStream& OutGeometryStream) const;

private:

    // Build a procedurally-generated mesh and append it to a geometry stream.
    virtual void Build(FProceduralGeometryStream& OutGeometryStream) const = 0;

};

// ==================================================================== //

/************************************************************************/
/* NON-MEMBER FUNCTIONS                                                 */
/************************************************************************/

// Append a procedural geometry item to a geometry stream.
FProceduralGeometryStream& operator<<(FProceduralGeometryStream& OutProceduralGeometryStream,
                                      const FProceduralMesh& InProceduralMesh);

// Append a procedural geometry item to a geometry stream.
FProceduralGeometryStream&& operator<<(FProceduralGeometryStream&& OutProceduralGeometryStream,
                                       const FProceduralMesh& InProceduralMesh);

// ==================================================================== //
