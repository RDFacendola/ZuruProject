
// ==================================================================== //

#include "ProceduralScaleModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL SCALE MODIFIER                                            */
/************************************************************************/

FProceduralScaleModifier::FProceduralScaleModifier(const FVector& InScale)
    : Scale(InScale)
    , InvScale(FVector::OneVector / InScale)
{

}

FProceduralScaleModifier::FProceduralScaleModifier(const FVector2D& InScale)
    : FProceduralScaleModifier(FVector{ InScale.X, InScale.Y, 1.0f })
{

}

FProceduralScaleModifier::FProceduralScaleModifier(float InScale)
    : FProceduralScaleModifier(FVector{ InScale })
{

}

void FProceduralScaleModifier::Bind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

void FProceduralScaleModifier::AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream)
{
    OutProceduralGeometryStream.AppendVertex({ InVertex.Position * Scale,
                                               (InVertex.Normal * InvScale).GetSafeNormal(),
                                               InVertex.UV });
}

void FProceduralScaleModifier::Unbind(FProceduralGeometryStream& OutProceduralGeometryStream)
{

}

// ==================================================================== //
