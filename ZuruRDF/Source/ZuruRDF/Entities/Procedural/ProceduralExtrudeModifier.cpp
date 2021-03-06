
// ==================================================================== //

#include "ProceduralExtrudeModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL EXTRUDE MODIFIER                                          */
/************************************************************************/

FProceduralExtrudeModifier::FProceduralExtrudeModifier(const FVector& InExtrusion)
    : Extrusion(InExtrusion)
{

}

FProceduralExtrudeModifier::FProceduralExtrudeModifier(float InExtrusion)
    : FProceduralExtrudeModifier(FVector::UpVector * InExtrusion)
{

}

void FProceduralExtrudeModifier::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralExtrudeModifier::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
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

void FProceduralExtrudeModifier::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
