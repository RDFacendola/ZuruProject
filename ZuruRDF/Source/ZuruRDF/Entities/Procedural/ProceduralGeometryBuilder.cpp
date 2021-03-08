
// ==================================================================== //


#include "ProceduralGeometryBuilder.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY BUILDER                                          */
/************************************************************************/

FProceduralGeometryBuilder::FProceduralGeometryBuilder(int32 InCapacity)
{
    Vertices.Reserve(InCapacity);
}

FProceduralGeometryStream& FProceduralGeometryBuilder::AppendVertex(const FProceduralVertex& InVertex)
{
    Vertices.Emplace(InVertex);

    Bounds += InVertex.Position;

    return *this;
}

const FProceduralVertex& FProceduralGeometryBuilder::GetVertex(int32 InIndex) const
{
    if (InIndex >= 0)
    {
        return Vertices[InIndex];                       // Forward.
    }
    else
    {
        return Vertices[Vertices.Num() + InIndex];      // Reverse.
    }
}

int32 FProceduralGeometryBuilder::GetVertexCount() const
{
    return Vertices.Num();
}

void FProceduralGeometryBuilder::Reset()
{
    Vertices.Reset();
}

FProceduralGeometryPrefab FProceduralGeometryBuilder::Build() const
{
    return { Vertices, Bounds };
}

const FBox& FProceduralGeometryBuilder::GetBounds() const
{
    return Bounds;
}

// ==================================================================== //
