
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL EXTRUDE MODIFIER                                          */
/************************************************************************/

//  A modifier that extrudes primitives passed through it.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralExtrudeModifier : public FProceduralGeometryModifier
{
public:

    // Create a new modifier by specifying the 3D extrusion direction and length.
    FProceduralExtrudeModifier(const FVector& InExtrusion);

    // Create a new modifier by specifying the 2D extrusion length along the Z axis.
    FProceduralExtrudeModifier(float InExtrusion);

    // Default copy-constructor.
    FProceduralExtrudeModifier(const FProceduralExtrudeModifier& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralExtrudeModifier() = default;

    // Default copy-assignment operator.
    FProceduralExtrudeModifier& operator=(const FProceduralExtrudeModifier& InRHS) = default;

    // Bind the modifier to a geometry stream.
    virtual void Bind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Called whenever a vertex is appended to a procedural geometry stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Unbind the modifier from a geometry stream.
    virtual void Unbind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

private:

    // Extrusion direction and length.
    FVector Extrusion{ FVector::UpVector };

    // Pending primitive.
    TArray<FProceduralVertex, TFixedAllocator<3>> Primitive;

    // Pending extruded primitive.
    TArray<FProceduralVertex, TFixedAllocator<3>> ExtrudedPrimitive;

};


// ==================================================================== //
