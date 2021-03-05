
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL NULL MODIFIER                                             */
/************************************************************************/

//  A simple modifier that discard all geometry passed through.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralNullModifier : public FProceduralGeometryModifier
{
public:

    // Default constructor.
    FProceduralNullModifier() = default;

    // Default copy-constructor.
    FProceduralNullModifier(const FProceduralNullModifier& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralNullModifier() = default;

    // Default copy-assignment operator.
    FProceduralNullModifier& operator=(const FProceduralNullModifier& InRHS) = default;

    // Bind the modifier to a geometry stream.
    virtual void Bind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Called whenever a vertex is appended to a procedural geometry stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Unbind the modifier from a geometry stream.
    virtual void Unbind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

};


// ==================================================================== //
