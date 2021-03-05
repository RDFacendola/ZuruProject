
// ==================================================================== //

#include "ProceduralQuad.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL QUAD                                                      */
/************************************************************************/

FProceduralQuad::FProceduralQuad(float InWidth, float InHeight)
    : FProceduralQuad(FVector2D{ InWidth, InHeight })
{

}

FProceduralQuad::FProceduralQuad(const FVector2D& InSize)
    : Size(0.0f, InSize.X, InSize.Y)
{

}

void FProceduralQuad::Build(FProceduralGeometryStream& OutGeometryStream) const
{
    OutGeometryStream.AppendVertex({ Size * FVector(-1.0f, -1.0f, -1.0f) });
    OutGeometryStream.AppendVertex({ Size * FVector(-1.0f, +1.0f, +1.0f) });
    OutGeometryStream.AppendVertex({ Size * FVector(-1.0f, -1.0f, +1.0f) });

    OutGeometryStream.AppendVertex({ Size * FVector(-1.0f, -1.0f, -1.0f) });
    OutGeometryStream.AppendVertex({ Size * FVector(-1.0f, +1.0f, -1.0f) });
    OutGeometryStream.AppendVertex({ Size * FVector(-1.0f, +1.0f, +1.0f) });
}

// ==================================================================== //

