
// ==================================================================== //

#include "ProceduralCube.h"

#include "ProceduralQuad.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL CUBE                                                      */
/************************************************************************/

FProceduralCube::FProceduralCube(float InDepth, float InWidth, float InHeight)
    : FProceduralCube(FVector{ InDepth, InWidth, InHeight })
{

}

FProceduralCube::FProceduralCube(const FVector& InSize)
    : Size(InSize)
{

}

void FProceduralCube::Build(FProceduralGeometryStream& OutGeometryStream) const
{
    auto FrontFace = FProceduralQuad{ Size.Y, Size.Z };
    auto RightFace = FProceduralQuad{ Size.X, Size.Z };
    auto TopFace = FProceduralQuad{ Size.Y, Size.X };


}

// ==================================================================== //

