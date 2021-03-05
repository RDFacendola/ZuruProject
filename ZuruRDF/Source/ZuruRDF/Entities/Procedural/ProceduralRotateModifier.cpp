
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
    OutProceduralGeometryStream.AppendVertex(InVertex * Rotation);
}

void FProceduralRotateModifier::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
