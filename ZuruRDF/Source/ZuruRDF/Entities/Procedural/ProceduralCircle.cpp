
// ==================================================================== //

#include "ProceduralCircle.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL CIRCLE                                                    */
/************************************************************************/

FProceduralCircle::FProceduralCircle(const FVector2D& InDiameter, int32 InTessellation)
    : Diameter{ InDiameter.X, InDiameter.Y, 0.0f }
    
{

}

void FProceduralCircle::Build(FProceduralGeometryStream& OutGeometryStream) const
{
    auto AngleStep = (2.0f * PI) / Tessellation;

    for (auto EdgeIndex = 0; EdgeIndex < Tessellation; ++EdgeIndex)
    {
        auto Angle0 = EdgeIndex * AngleStep;
        auto Angle1 = Angle0 + AngleStep;

        auto XY0 = FVector::ZeroVector;
        auto XY1 = FVector{ FMath::Cos(Angle0), FMath::Sin(Angle0), 0.0f } * Diameter * 0.5f;
        auto XY2 = FVector{ FMath::Cos(Angle1), FMath::Sin(Angle1), 0.0f } * Diameter * 0.5f;

        OutGeometryStream
            .AppendVertex(FProceduralVertex{ XY0 })
            .AppendVertex(FProceduralVertex{ XY2 })
            .AppendVertex(FProceduralVertex{ XY1 });
    }
}

// ==================================================================== //

