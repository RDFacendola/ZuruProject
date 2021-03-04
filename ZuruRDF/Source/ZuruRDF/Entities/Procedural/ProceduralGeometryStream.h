
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
    ~FProceduralGeometryStream() = default;

    // Append a new vertex to the stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex) = 0;

    // Get a vertex by index.
    // Negative index access the underlying stream in reverse order.
    // If the provided index exceeds stream range, the behavior of this method is undefined.
    virtual const FProceduralVertex& GetVertex(int32 InIndex) const = 0;

    // Get the number of vertices appended so far.
    virtual int32 GetVertexCount() const = 0;

};

// ==================================================================== //
