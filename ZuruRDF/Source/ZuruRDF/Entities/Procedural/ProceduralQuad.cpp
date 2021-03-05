
// ==================================================================== //

#include "ProceduralQuad.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL QUAD                                                      */
/************************************************************************/

FProceduralQuad::FProceduralQuad(const FVector2D& InSize)
    : Size(InSize.X, InSize.Y, 0.0f)
{

}

void FProceduralQuad::Build(FProceduralGeometryStream& OutGeometryStream) const
{
    OutGeometryStream
        .AppendVertex({ Size * FVector{ -1.0f, -1.0f, 0.0f } })
        .AppendVertex({ Size * FVector{ -1.0f, +1.0f, 0.0f } })
        .AppendVertex({ Size * FVector{ +1.0f, +1.0f, 0.0f } });

    OutGeometryStream
        .AppendVertex({ Size * FVector{ -1.0f, -1.0f, 0.0f } })
        .AppendVertex({ Size * FVector{ +1.0f, +1.0f, 0.0f } })
        .AppendVertex({ Size * FVector{ +1.0f, -1.0f, 0.0f } });
}

// ==================================================================== //

