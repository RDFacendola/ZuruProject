
// ==================================================================== //

#include "ProceduralScale.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL SCALE                                                     */
/************************************************************************/

FProceduralScale::FProceduralScale(const FVector& InScale)
    : Scale(InScale)
{

}

FProceduralScale::FProceduralScale(const FVector2D& InScale)
    : FProceduralScale(FVector{ InScale.X, InScale.Y, 1.0f })
{

}

FProceduralScale::FProceduralScale(float InScale)
    : FProceduralScale(FVector{ InScale })
{

}

void FProceduralScale::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralScale::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    OutProceduralGeometryStream.AppendVertex(InVertex * Scale);
}

void FProceduralScale::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
