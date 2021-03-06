
// ==================================================================== //

#include "ProceduralRotate.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL ROTATE                                                    */
/************************************************************************/

FProceduralRotate::FProceduralRotate(const FRotator& InRotation)
    : Rotation(InRotation)
{

}

void FProceduralRotate::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralRotate::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    OutProceduralGeometryStream.AppendVertex(InVertex * Rotation);
}

void FProceduralRotate::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
