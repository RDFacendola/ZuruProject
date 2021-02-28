
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
// This component is meant to aggregate raw inputs from the user and send relative actions to the pawn.
// This component automatically binds to a FreeCameraComponent counterpart upon pawn possession.
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

private:

	// Get the strafe input.
	FVector2D GetStrafeInput() const;

	// Consume all inputs.
	void ConsumeInputs();

	// Called whenever the camera forward/backward input is detected.
	void OnForwardInput(float InValue);

	// Called whenever the camera right/left input is detected.
	void OnRightInput(float InValue);

	// Called whenever the camera orbit input is detected.
	void OnOrbitInput(float InValue);

	// Called whenever the camera pivot input is detected.
	void OnPivotInput(float InValue);

	// Called whenever the camera distance input is detected.
	void OnDistanceInput(float InValue);

	// Called whenever the camera orbit snap right input is pressed.
	void OnOrbitSnapRightPressed();

	// Called whenever the camera orbit snap left input is pressed.
	void OnOrbitSnapLeftPressed();

	// Called whenever the camera orbit snap right input is released.
	void OnOrbitSnapRightReleased();

	// Called whenever the camera orbit snap left input is released.
	void OnOrbitSnapLeftReleased();

	// The free-camera component counterpart on the pawn.
	UPROPERTY()
	UFreeCameraComponent* FreeCameraComponent{ nullptr };

	// Movement in the XY plane.
	FVector2D StrafeInput;

	// Orbit input.
	float OrbitInput{ 0.0f };

	// Pivot input.
	float PivotInput{ 0.0f };

	// Distance input.
	float DistanceInput{ 0.0f };

	// Orbit snap right.
	bool bOrbitSnapRight{ false };

	// Orbit snap left.
	bool bOrbitSnapLeft{ false };

	// Enable the actual orbit snap left action. Avoids repeating the action while the keys are pressed.
	bool bOrbitSnapRightEnabled{ true };

	// Enable the actual orbit snap right action. Avoids repeating the action while the keys are pressed.
	bool bOrbitSnapLeftEnabled{ true };

};

// ==================================================================== //
