
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryModifier.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL MIRROR                                                    */
/************************************************************************/

//  A modifier that duplicates and mirrors primitives passed through it.
//  Mirroring is performed with respect to a user-defined plane.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralMirror : public FProceduralGeometryModifier
{
public:

    // Create a new modifier by specifying the 3D mirroring plane by its normal.
    FProceduralMirror(const FPlane& InMirrorPlane);

    // Create a new modifier by specifying the 3D mirroring plane by its normal.
    FProceduralMirror(const FVector& InMirrorPlaneNormal);
    
    // Create a new modifier by specifying the 2D mirroring plane by its normal.
    FProceduralMirror(const FVector2D& InMirrorPlaneNormal);

    // Default copy-constructor.
    FProceduralMirror(const FProceduralMirror& InRHS) = default;

    // Default virtual destructor.
    virtual ~FProceduralMirror() = default;

    // Default copy-assignment operator.
    FProceduralMirror& operator=(const FProceduralMirror& InRHS) = default;

    // Bind the modifier to a geometry stream.
    virtual void Bind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Called whenever a vertex is appended to a procedural geometry stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream) override;

    // Unbind the modifier from a geometry stream.
    virtual void Unbind(FProceduralGeometryStream& OutProceduralGeometryStream) override;

private:

    // Mirror plane.
    FPlane MirrorPlane{ FVector::RightVector, 0.0f };

    // Pending primitive.
    TArray<FProceduralVertex, TFixedAllocator<3>> Primitive;

};


// ==================================================================== //
