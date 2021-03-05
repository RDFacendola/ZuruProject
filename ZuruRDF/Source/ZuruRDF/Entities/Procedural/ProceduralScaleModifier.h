
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL SCALE MODIFIER                                            */
/************************************************************************/

//  A modifier that scales vertices and normals passed through it.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralScaleModifier : public FProceduralGeometryModifier
{
public:

    // Default constructor.
    FProceduralScaleModifier() = default;

    // Create a new modifier from a 3D scale.
    FProceduralScaleModifier(const FVector& InScale);

    // Create a new modifier from a 2D scale.
    FProceduralScaleModifier(const FVector2D& InScale);

    // Create a new modifier from an uniform scale.
    FProceduralScaleModifier(float InScale);

    // Default copy-constructor.
    FProceduralScaleModifier(const FProceduralScaleModifier& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralScaleModifier() = default;

    // Default copy-assignment operator.
    FProceduralScaleModifier& operator=(const FProceduralScaleModifier& InRHS) = default;

    // Bind the modifier to a geometry stream.
    virtual void Bind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Called whenever a vertex is appended to a procedural geometry stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Unbind the modifier from a geometry stream.
    virtual void Unbind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

private:

    // Scale applied to each vertex.
    FVector Scale{ FVector::OneVector };

};


// ==================================================================== //
