
// ==================================================================== //

#include "ProceduralTranslateModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL TRANSLATE MODIFIER                                        */
/************************************************************************/

FProceduralTranslateModifier::FProceduralTranslateModifier(const FVector& InTranslation)
    : Translation(InTranslation)
{

}

FProceduralTranslateModifier::FProceduralTranslateModifier(const FVector2D& InTranslation)
    : FProceduralTranslateModifier( FVector{ InTranslation.X, InTranslation.Y, 0.0f } )
{

}

void FProceduralTranslateModifier::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralTranslateModifier::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    OutProceduralGeometryStream.AppendVertex({ InVertex.Position + Translation, InVertex.Normal, InVertex.UV });
}

void FProceduralTranslateModifier::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
