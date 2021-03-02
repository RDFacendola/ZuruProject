
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Math/Vector.h"
#include "Math/Rotator.h"

#include "ProceduralGizmo.generated.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GIZMO                                                     */
/************************************************************************/

// Represents a gizmo whose local transform influence the shape of a procedural geometry.
//
// Gizmo are defined as a linear combination of two transforms.
//
// @author Raffaele D. Facendola - March 2021.
USTRUCT()
struct ZURURDF_API FProceduralGizmo
{
	GENERATED_BODY()
	
public:

	// Create a new procedural gizmo  with an empty transform space.
	FProceduralGizmo() = default;

	// Create a new procedural gizmo given its transform space.
	FProceduralGizmo(const FTransform& InBasis0, const FTransform& InBasis1);

	// Get the linear combination factors for gizmo translation. Returned values are defined in the range (<0,0,0>, <1,1,1>).
	FVector GetTranslationWeight() const;

	// Get the linear combination factors for gizmo rotation. Returned values are defined in the range (<0,0,0>, <1,1,1>).
	FVector GetRotationWeight() const;

	// Get the linear combination factors for gizmo scale. Returned values are defined in the range (<0,0,0>, <1,1,1>).
	FVector GetScaleWeight() const;

	// Get current gizmo transform.
	const FTransform& GetTransform() const;

	// Set current gizmo transform.
	// This function automatically clamps the input transform in the gizmo range.
	void SetTransform(const FTransform& InTransform);

private:

	// Gizmo transform, in local space.
	UPROPERTY(VisibleAnywhere, Category = Transform)
	FTransform Transform;

	// First transform basis, in local space.
	UPROPERTY(VisibleAnywhere, Category = Transform)
	FTransform TransformBasis0;

	// Seconds transform basis, in local space.
	UPROPERTY(VisibleAnywhere, Category = Transform)
	FTransform TransformBasis1;

};

// ==================================================================== //
