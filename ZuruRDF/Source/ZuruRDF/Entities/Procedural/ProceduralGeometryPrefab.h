
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"

#include "ProceduralVertex.h"
#include "ProceduralMeshComponent.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY PREFAB                                           */
/************************************************************************/

// Represents a "blueprint" to generate procedural mesh component sections.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralGeometryPrefab
{
public:

    // Default constructor.
    FProceduralGeometryPrefab() = default;

    // Create a new prefab.
    FProceduralGeometryPrefab(const TArray<FProceduralVertex>& InVertices);

    // Default copy-constructor.
    FProceduralGeometryPrefab(const FProceduralGeometryPrefab& InRHS) = default;

    // Default copy-assignment operator.
    FProceduralGeometryPrefab& operator=(const FProceduralGeometryPrefab& InRHS) = default;

    // Default destructor.
    ~FProceduralGeometryPrefab() = default;

    // Create a mesh section to a procedural mesh component, overwriting an existing one, if possible.
    void Generate(UProceduralMeshComponent& InProceduralMeshComponent, int32 InMeshSection) const;

private:

    // Vertex positions.
    TArray<FVector> Positions;

    // Vertex normals.
    TArray<FVector> Normals;

    // Vertex UVs.
    TArray<FVector2D> UVs;

    // Vertex indices.
    TArray<int32> Indices;

};

// ==================================================================== //
