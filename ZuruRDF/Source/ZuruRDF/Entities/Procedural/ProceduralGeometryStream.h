
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"

#include "ProceduralVertex.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY STREAM                                           */
/************************************************************************/

// An interface for a stream procedurally-generated vertices can be appended to.
//
// The stream assumes triangle-list topology and counter-clockwise culling.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralGeometryStream
{
public:

    // Default virtual destructor.
    virtual ~FProceduralGeometryStream() = default;

    // Append a new vertex to the stream and return a reference to self.
    virtual FProceduralGeometryStream& AppendVertex(const FProceduralVertex& InVertex) = 0;

    // Get a vertex by index.
    // Negative index access the underlying stream in reverse order.
    // If the provided index exceeds stream range, the behavior of this method is undefined.
    virtual const FProceduralVertex& GetVertex(int32 InIndex) const = 0;

    // Get the number of vertices appended so far.
    virtual int32 GetVertexCount() const = 0;

};

// ==================================================================== //
