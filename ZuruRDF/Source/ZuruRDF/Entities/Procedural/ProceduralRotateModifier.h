
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL ROTATE MODIFIER                                           */
/************************************************************************/

//  A modifier that rotates vertices and normals passed through it.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralRotateModifier : public FProceduralGeometryModifier
{
public:

    // Default constructor.
    FProceduralRotateModifier() = default;

    // Create a new modifier from a rotation.
    FProceduralRotateModifier(const FRotator& InRotation);

    // Default copy-constructor.
    FProceduralRotateModifier(const FProceduralRotateModifier& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralRotateModifier() = default;

    // Default copy-assignment operator.
    FProceduralRotateModifier& operator=(const FProceduralRotateModifier& InRHS) = default;

    // Bind the modifier to a geometry stream.
    virtual void Bind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Called whenever a vertex is appended to a procedural geometry stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Unbind the modifier from a geometry stream.
    virtual void Unbind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

private:

    // Rotation applied to each vertex.
    FRotator Rotation{ FRotator::ZeroRotator };

};


// ==================================================================== //
