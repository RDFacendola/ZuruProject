
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FreeCameraComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA COMPONENT                                                */
/************************************************************************/

// A free camera component used to navigate the world from the above.
//
// The camera has three movements:
//
// Strafe: moves the camera in the XY plane.
// Orbit: orbit the camera around its target along the Z axis.
// Pivot: raise or lower the camera angle relative to its target.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API UFreeCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Minimum pivot value, in degrees.
	static constexpr auto kMinPivot = 0.0f;

	// Maximum pivot value, in degrees.
	static constexpr auto kMaxPivot = 90.0f;

	// Bind to an input component.
	void Bind(UInputComponent& InInputComponent);

	// Set the camera location.
	void SetLocation(const FVector2D& InLocation);

	// Set the camera orbit.
	void SetOrbit(float InOrbit);

	// Set the camera pivot.
	void SetPivot(float InPivot);

	// Get the camera location.
	const FVector2D& GetLocation() const;

	// Get the camera orbit.
	float GetOrbit() const;

	// Get the camera pivot.
	float GetPivot() const;

	void TickComponent(float InDeltaTime, enum ELevelTick InTickType, FActorComponentTickFunction* InTickFunction) override;

private:

	// Called whenever the camera forward/backward input is detected.
	void OnForwardInput(float InValue);

	// Called whenever the camera right/left input is detected.
	void OnRightInput(float InValue);

	// Called whenever the camera orbit input is detected.
	void OnOrbitInput(float InValue);

	// Called whenever the camera pivot input is detected.
	void OnPivotInput(float InValue);

	// Movement speed, in world units per second.
	UPROPERTY(Category = Camera, EditAnywhere)
	float StrafeSpeed = { 10.0f };

	// Orbit speed, in degrees per second.
	UPROPERTY(Category = Camera, EditAnywhere)
	float OrbitSpeed = { 180.0f };

	// Pivot speed, in degrees per second.
	UPROPERTY(Category = Camera, EditAnywhere)
	float PivotSpeed{ 45.0f };

	// Movement smoothing.
	UPROPERTY(Category = Camera, EditAnywhere)
	float StrafeSmooth{ 0.0f };

	// Orbit smoothing.
	UPROPERTY(Category = Camera, EditAnywhere)
	float OrbitSmooth{ 0.0f };

	// Pivot smoothing.
	UPROPERTY(Category = Camera, EditAnywhere)
	float PivotSmooth{ 0.0f };

	// Movement in the XY plane.
	FVector2D StrafeInput;

	// Orbit input.
	float OrbitInput{ 0.0f };

	// Pivot input.
	float PivotInput{ 0.0f };

	// Target camera location, in world units.
	FVector2D TargetLocation;

	// Target camera orbit, in degrees.
	float TargetOrbit{ 0.0f };

	// Target camera pivot, in degrees.
	float TargetPivot{ 0.0f };

	// Current camera location, in world units.
	FVector2D Location;

	// Current camera orbit, in degrees.
	float Orbit{ 0.0f };

	// Current camera pivot, in degrees.
	float Pivot{ 0.0f };

};

// ==================================================================== //
