
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "ProceduralGizmo.h"

#include "ProceduralGeometryComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY COMPONENT                                        */
/************************************************************************/

// Represents a geometry whose shape can be generated and driven procedurally.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Procedural)
class ZURURDF_API UProceduralGeometryComponent : public USceneComponent
{
	GENERATED_BODY()
	
public:

	// Access the gizmos used to drive the procedural geometry.
	const TArray<FProceduralGizmo>& GetGizmos() const;

protected:

private:

	// Gizmo used to drive the geometry shape.
	UPROPERTY(VisibleAnywhere)
	TArray<FProceduralGizmo> Gizmos;

};

// ==================================================================== //
