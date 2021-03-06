
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"

#include "ProceduralVertex.h"
#include "ProceduralGeometryStream.h"
#include "ProceduralGeometryPrefab.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY BUILDER                                          */
/************************************************************************/

// Builder class that accepts any number of procedural meshes
// and modifiers and produce procedurally-generated prefabs.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralGeometryBuilder : public FProceduralGeometryStream
{
public:

    // Create a new mesh builder.
    // @param InCapacity Initial vertex capacity. Can be exceeded.
    FProceduralGeometryBuilder(int32 InCapacity = 1024);

    // Default copy-constructor.
    FProceduralGeometryBuilder(const FProceduralGeometryBuilder& InRHS) = default;

    // Default move-constructor.
    FProceduralGeometryBuilder(FProceduralGeometryBuilder&& InRHS) = default;

    // Default copy-assignment operator.
    FProceduralGeometryBuilder& operator=(const FProceduralGeometryBuilder& InRHS) = default;

    // Default move-assignment operator.
    FProceduralGeometryBuilder& operator=(FProceduralGeometryBuilder&& InRHS) = default;

    // Default destructor.
    ~FProceduralGeometryBuilder() = default;

    // Discard procedural geometry generated so far on this builder.
    void Reset();

    // Build a prefab with the geometry assigned so far.
    FProceduralGeometryPrefab Build() const;

    virtual FProceduralGeometryStream& AppendVertex(const FProceduralVertex& InVertex) override;

    virtual const FProceduralVertex& GetVertex(int32 InIndex) const override;

    virtual int32 GetVertexCount() const override;

private:

    // Procedurally-generated vertices.
    TArray<FProceduralVertex> Vertices;

};

// ==================================================================== //
