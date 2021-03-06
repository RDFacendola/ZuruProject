
// ==================================================================== //

#include "ProceduralMirror.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL MIRROR                                                    */
/************************************************************************/

FProceduralMirror::FProceduralMirror(const FPlane& InMirrorPlane)
    : MirrorPlane(InMirrorPlane)
{

}

FProceduralMirror::FProceduralMirror(const FVector& InMirrorPlaneNormal)
    : FProceduralMirror(FPlane{ InMirrorPlaneNormal, 0.0f })
{

}

FProceduralMirror::FProceduralMirror(const FVector2D& InMirrorPlaneNormal)
    : FProceduralMirror(FVector{ InMirrorPlaneNormal.X, InMirrorPlaneNormal.Y, 0.0f })
{

}

void FProceduralMirror::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralMirror::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
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

void FProceduralMirror::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
