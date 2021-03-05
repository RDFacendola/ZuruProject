
// ==================================================================== //


#include "ProceduralIdentityModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL IDENTITY MODIFIER                                         */
/************************************************************************/

void FProceduralIdentityModifier::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralIdentityModifier::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    OutProceduralGeometryStream.AppendVertex(InVertex);
}

void FProceduralIdentityModifier::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
