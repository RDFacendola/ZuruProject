
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL TRANSLATE                                                 */
/************************************************************************/

//  A modifier that translate vertices passed through it.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralTranslate : public FProceduralGeometryModifier
{
public:

    // Default constructor.
    FProceduralTranslate() = default;

    // Create a new modifier from a 3D translation vector.
    FProceduralTranslate(const FVector& InTranslation);

    // Create a new modifier from a 2D translation vector.
    FProceduralTranslate(const FVector2D& InTranslation);

    // Default copy-constructor.
    FProceduralTranslate(const FProceduralTranslate& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralTranslate() = default;

    // Default copy-assignment operator.
    FProceduralTranslate& operator=(const FProceduralTranslate& InRHS) = default;

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
