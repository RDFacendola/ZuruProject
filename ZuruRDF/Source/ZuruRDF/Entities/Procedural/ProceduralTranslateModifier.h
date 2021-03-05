
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL TRANSLATE MODIFIER                                        */
/************************************************************************/

//  A modifier that translate vertices passed through it.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralTranslateModifier : public FProceduralGeometryModifier
{
public:

    // Default constructor.
    FProceduralTranslateModifier() = default;

    // Create a new modifier from a 3D translation vector.
    FProceduralTranslateModifier(const FVector& InTranslation);

    // Create a new modifier from a 2D translation vector.
    FProceduralTranslateModifier(const FVector2D& InTranslation);

    // Default copy-constructor.
    FProceduralTranslateModifier(const FProceduralTranslateModifier& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralTranslateModifier() = default;

    // Default copy-assignment operator.
    FProceduralTranslateModifier& operator=(const FProceduralTranslateModifier& InRHS) = default;

    // Bind the modifier to a geometry stream.
    virtual void Bind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Called whenever a vertex is appended to a procedural geometry stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Unbind the modifier from a geometry stream.
    virtual void Unbind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

private:

    // Translation applied to each vertex.
    FVector Translation{ FVector::ZeroVector };

};


// ==================================================================== //
