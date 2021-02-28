
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FreeCameraComponent.h"

#include "FreeCameraInputComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA INPUT COMPONENT                                          */
/************************************************************************/

// A component used to read free-camera inputs on a player controller.
//
// This component automatically binds to a FreeCameraComponent counterpart upon pawn possession and sends relevant commands.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API UFreeCameraInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Bind to an input component.
	void Bind(UInputComponent& InInputComponent);

	// Bind to a pawn.
	void Bind(APawn& InPawn);

	// Advance the component status.
	void Advance(float InDeltaSeconds);

	// Get the strafe input.
	FVector2D GetStrafe() const;

	// Get the orbit input.
	float GetOrbit() const;

	// Get the pivot input.
	float GetPivot() const;

	// Consume all inputs.
	void ConsumeInputs();

private:

	// Called whenever the camera forward/backward input is detected.
	void OnForwardInput(float InValue);

	// Called whenever the camera right/left input is detected.
	void OnRightInput(float InValue);

	// Called whenever the camera orbit input is detected.
	void OnOrbitInput(float InValue);

	// Called whenever the camera pivot input is detected.
	void OnPivotInput(float InValue);

	// The free-camera component counterpart on the pawn.
	UPROPERTY()
	UFreeCameraComponent* FreeCameraComponent{ nullptr };

	// Movement in the XY plane.
	FVector2D StrafeInput;

	// Orbit input.
	float OrbitInput{ 0.0f };

	// Pivot input.
	float PivotInput{ 0.0f };

};

// ==================================================================== //
