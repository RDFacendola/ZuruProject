
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"

#include "FreeCameraComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA COMPONENT                                                */
/************************************************************************/

// A free camera component used to navigate the world from the above.
//
// The camera has four movements:
//
// Strafe: moves the camera in the XY plane.
// Orbit: orbit the camera around its target along the Z axis.
// Pivot: raise or lower the camera angle relative to its target.
// Distance: moves towards/away from the camera target.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API UFreeCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:

	// Create a new free camera component.
	UFreeCameraComponent();

	// Called whenever a strafe input is detected.
	void OnStrafeInput(const FVector2D& InStrafe);

	// Called whenever an orbit input is detected.
	void OnOrbitInput(float InOrbit);

	// Called whenever a pivot input is detected.
	void OnPivotInput(float InPivot);

	// Called whenever a distance input is detected.
	void OnDistanceInput(float InDistance);

	// Advance the component status.
	void Advance(float InDeltaTime);

	void BeginPlay() override;

private:
	
	// Minimum angle between the camera and its target, in degrees.
	UPROPERTY(Category = Camera, EditAnywhere)
	float MinPivot{ 0.0f };

	// Maximum angle between the camera and its target, in degrees.
	UPROPERTY(Category = Camera, EditAnywhere)
	float MaxPivot{ 90.0f };

	// Minimum distance of the camera from the target, in world units.
	UPROPERTY(Category = Camera, EditAnywhere)
	float MinDistance{ 200.0f };

	// Maximum distance of the camera from the target, in world units.
	UPROPERTY(Category = Camera, EditAnywhere)
	float MaxDistance{ 2000.0f };

	// Desired vertical offset of the camera relative to its target, in world units.
	UPROPERTY(Category = Camera, EditAnywhere)
	float VerticalOffset{ 50.0f };

	// Movement speed, in world units per second.
	UPROPERTY(Category = Camera, EditAnywhere)
	float StrafeSpeed = { 10.0f };

	// Orbit speed, in degrees per second.
	UPROPERTY(Category = Camera, EditAnywhere)
	float OrbitSpeed = { 180.0f };

	// Pivot speed, in degrees per second.
	UPROPERTY(Category = Camera, EditAnywhere)
	float PivotSpeed{ 45.0f };

	// Distance speed, in distance percentage per second.
	UPROPERTY(Category = Camera, EditAnywhere)
	float DistanceSpeed{ 10.0f };

	// Movement smoothing.
	UPROPERTY(Category = Camera, EditAnywhere)
	float StrafeSmooth{ 0.0f };

	// Orbit smoothing.
	UPROPERTY(Category = Camera, EditAnywhere)
	float OrbitSmooth{ 0.0f };

	// Pivot smoothing.
	UPROPERTY(Category = Camera, EditAnywhere)
	float PivotSmooth{ 0.0f };

	// Distance smoothing.
	UPROPERTY(Category = Camera, EditAnywhere)
	float DistanceSmooth{ 0.0f };

	// Movement in the XY plane.
	FVector2D StrafeInput;

	// Orbit input.
	float OrbitInput{ 0.0f };

	// Pivot input.
	float PivotInput{ 0.0f };

	// Distance input.
	float DistanceInput{ 0.0f };

	// Target camera location, in world units.
	FVector2D TargetLocation;

	// Target camera orbit, in degrees.
	float TargetOrbit{ 0.0f };

	// Target camera pivot, in degrees.
	float TargetPivot{ 0.0f };

	// Target camera distance, in world units.
	float TargetDistance{ 200.0f };

	// Distance of the camera from its target.
	float Distance{ 200.0f };
};

// ==================================================================== //
