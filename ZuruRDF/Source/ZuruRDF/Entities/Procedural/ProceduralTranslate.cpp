
// ==================================================================== //

#include "ProceduralTranslate.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL TRANSLATE                                                 */
/************************************************************************/

FProceduralTranslate::FProceduralTranslate(const FVector& InTranslation)
    : Translation(InTranslation)
{

}

FProceduralTranslate::FProceduralTranslate(const FVector2D& InTranslation)
    : FProceduralTranslate( FVector{ InTranslation.X, InTranslation.Y, 0.0f } )
{

}

void FProceduralTranslate::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralTranslate::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    OutProceduralGeometryStream.AppendVertex(InVertex + Translation);
}

void FProceduralTranslate::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
