
// ==================================================================== //

#include "ProceduralRotateModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL ROTATE MODIFIER                                           */
/************************************************************************/

FProceduralRotateModifier::FProceduralRotateModifier(const FRotator& InRotation)
    : Rotation(InRotation)
{

}

void FProceduralRotateModifier::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralRotateModifier::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    OutProceduralGeometryStream.AppendVertex({ Rotation.RotateVector(InVertex.Position), Rotation.RotateVector(InVertex.Normal), InVertex.UV });
}

void FProceduralRotateModifier::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
