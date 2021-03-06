
// ==================================================================== //

#include "ProceduralIdentity.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL IDENTITY                                                  */
/************************************************************************/

void FProceduralIdentity::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralIdentity::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    OutProceduralGeometryStream.AppendVertex(InVertex);
}

void FProceduralIdentity::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
