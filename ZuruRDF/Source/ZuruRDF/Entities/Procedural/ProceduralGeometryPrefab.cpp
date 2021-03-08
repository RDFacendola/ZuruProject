
// ==================================================================== //


#include "ProceduralGeometryPrefab.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY PREFAB                                           */
/************************************************************************/

FProceduralGeometryPrefab::FProceduralGeometryPrefab(const TArray<FProceduralVertex>& InVertices, const FBox& InBounds)
    : Bounds(InBounds)
{
    auto Count = InVertices.Num();

    Positions.Reset(Count);
    Normals.Reset(Count);
    UVs.Reset(Count);
    Indices.Reset(Count);

    for (auto&& Vertex : InVertices)
    {
        Positions.Emplace(Vertex.Position);
        Normals.Emplace(Vertex.Normal);
        UVs.Emplace(Vertex.UV);
        Indices.Emplace(Indices.Num());
    }
}

void FProceduralGeometryPrefab::Generate(UProceduralMeshComponent& InProceduralMeshComponent, int32 InMeshSection) const
{
    InProceduralMeshComponent.CreateMeshSection(InMeshSection, Positions, Indices, Normals, UVs, TArray<FColor>{}, TArray<FProcMeshTangent>{}, false);
}

const FBox& FProceduralGeometryPrefab::GetBounds() const
{
    return Bounds;
}

// ==================================================================== //
