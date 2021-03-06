
// ==================================================================== //

#include "ProceduralMirrorModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL MIRROR MODIFIER                                           */
/************************************************************************/

FProceduralMirrorModifier::FProceduralMirrorModifier(const FPlane& InMirrorPlane)
    : MirrorPlane(InMirrorPlane)
{

}

FProceduralMirrorModifier::FProceduralMirrorModifier(const FVector& InMirrorPlaneNormal)
    : FProceduralMirrorModifier(FPlane{ InMirrorPlaneNormal, 0.0f })
{

}

FProceduralMirrorModifier::FProceduralMirrorModifier(const FVector2D& InMirrorPlaneNormal)
    : FProceduralMirrorModifier(FVector{ InMirrorPlaneNormal.X, InMirrorPlaneNormal.Y, 0.0f })
{

}

void FProceduralMirrorModifier::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralMirrorModifier::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    // Append the desired vertex.

    OutProceduralGeometryStream.AppendVertex(InVertex);

    // Store the mirrored vertex.

    Primitive.Emplace(FProceduralVertex
    {
        InVertex.Position.MirrorByPlane(MirrorPlane),
        InVertex.Normal.MirrorByVector(MirrorPlane),
        InVertex.UV
    });

    // Append the full mirrored primitive once complete.

    if (Primitive.Num() == 3)
    {
        // Mirrored vertices needs to be resorted as the mirroring process flips the primitive's backface.

        OutProceduralGeometryStream
            .AppendVertex(Primitive[0])
            .AppendVertex(Primitive[2])
            .AppendVertex(Primitive[1]);

        Primitive.Reset();
    }
}

void FProceduralMirrorModifier::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
