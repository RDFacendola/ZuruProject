
// ==================================================================== //

#include "ProceduralExtrude.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL EXTRUDE                                                   */
/************************************************************************/

FProceduralExtrude::FProceduralExtrude(const FVector& InExtrusion)
    : Extrusion(InExtrusion)
{

}

FProceduralExtrude::FProceduralExtrude(float InExtrusion)
    : FProceduralExtrude(FVector::UpVector * InExtrusion)
{

}

void FProceduralExtrude::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralExtrude::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    // Store a copy of the vertex and its extrusion.

    Primitive.Emplace(InVertex);
    ExtrudedPrimitive.Emplace(InVertex + Extrusion);
    
    // Extrude the full primitive once complete.

    if (Primitive.Num() == 3)
    {
        OutProceduralGeometryStream
            .AppendVertex(Primitive[0]).AppendVertex(Primitive[2]).AppendVertex(Primitive[1])

            .AppendVertex(Primitive[0]).AppendVertex(Primitive[1]).AppendVertex(ExtrudedPrimitive[1])
            .AppendVertex(Primitive[0]).AppendVertex(ExtrudedPrimitive[1]).AppendVertex(ExtrudedPrimitive[0])

            .AppendVertex(Primitive[1]).AppendVertex(Primitive[2]).AppendVertex(ExtrudedPrimitive[2])
            .AppendVertex(Primitive[1]).AppendVertex(ExtrudedPrimitive[2]).AppendVertex(ExtrudedPrimitive[1])

            .AppendVertex(Primitive[2]).AppendVertex(Primitive[0]).AppendVertex(ExtrudedPrimitive[0])
            .AppendVertex(Primitive[2]).AppendVertex(ExtrudedPrimitive[0]).AppendVertex(ExtrudedPrimitive[2])

            .AppendVertex(ExtrudedPrimitive[0]).AppendVertex(ExtrudedPrimitive[1]).AppendVertex(ExtrudedPrimitive[2]);

        Primitive.Reset();
        ExtrudedPrimitive.Reset();
    }
}

void FProceduralExtrude::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
