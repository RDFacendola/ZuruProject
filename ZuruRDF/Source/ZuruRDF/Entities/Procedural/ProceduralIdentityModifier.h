
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL IDENTITY MODIFIER                                         */
/************************************************************************/

//  A simple modifier that acts a pass-through.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralIdentityModifier : public FProceduralGeometryModifier
{
public:

    // Default constructor.
    FProceduralIdentityModifier() = default;

    // Default copy-constructor.
    FProceduralIdentityModifier(const FProceduralIdentityModifier& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralIdentityModifier() = default;

    // Default copy-assignment operator.
    FProceduralIdentityModifier& operator=(const FProceduralIdentityModifier& InRHS) = default;

    // Bind the modifier to a geometry stream.
    virtual void Bind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Called whenever a vertex is appended to a procedural geometry stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Unbind the modifier from a geometry stream.
    virtual void Unbind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

};


// ==================================================================== //
