
// ==================================================================== //

#include "FreeCameraInputComponent.h"

#include "ZuruRDF/GameModes/Inputs/CameraInputs.h"

// ==================================================================== //

void UFreeCameraInputComponent::Bind(UInputComponent& InInputComponent)
{
	InInputComponent.BindAxis(FCameraInputs::kCameraForward, this, &UFreeCameraInputComponent::OnForwardInput);
	InInputComponent.BindAxis(FCameraInputs::kCameraRight, this, &UFreeCameraInputComponent::OnRightInput);
	InInputComponent.BindAxis(FCameraInputs::kCameraOrbit, this, &UFreeCameraInputComponent::OnOrbitInput);
	InInputComponent.BindAxis(FCameraInputs::kCameraPivot, this, &UFreeCameraInputComponent::OnPivotInput);
	InInputComponent.BindAxis(FCameraInputs::kCameraDistance, this, &UFreeCameraInputComponent::OnDistanceInput);

	InInputComponent.BindAction(FCameraInputs::kCameraOrbitSnapRightAction, IE_Pressed, this, &UFreeCameraInputComponent::OnOrbitSnapRightPressed);
	InInputComponent.BindAction(FCameraInputs::kCameraOrbitSnapLeftAction, IE_Pressed, this, &UFreeCameraInputComponent::OnOrbitSnapLeftPressed);

	InInputComponent.BindAction(FCameraInputs::kCameraOrbitSnapRightAction, IE_Released, this, &UFreeCameraInputComponent::OnOrbitSnapRightReleased);
	InInputComponent.BindAction(FCameraInputs::kCameraOrbitSnapLeftAction, IE_Released, this, &UFreeCameraInputComponent::OnOrbitSnapLeftReleased);
}

void UFreeCameraInputComponent::Bind(APawn& InPawn)
{
	FreeCameraComponent = InPawn.FindComponentByClass<UFreeCameraComponent>();
}

void UFreeCameraInputComponent::Advance(float InDeltaSeconds)
{
	if (FreeCameraComponent)
	{
		FreeCameraComponent->OnStrafeInput(GetStrafeInput());
		FreeCameraComponent->OnPivotInput(PivotInput);
		FreeCameraComponent->OnDistanceInput(DistanceInput);
		
		if (bOrbitSnapRight)
		{
			FreeCameraComponent->OnOrbitSnapRightInput();
		}
		else if ((OrbitInput > 0.0f) && bOrbitSnapRightEnabled)
		{
			FreeCameraComponent->OnOrbitInput(OrbitInput);
		}

		if (bOrbitSnapLeft)
		{
			FreeCameraComponent->OnOrbitSnapLeftInput();
		}
		else if ((OrbitInput < 0.0f) && bOrbitSnapLeftEnabled)
		{
			FreeCameraComponent->OnOrbitInput(OrbitInput);
		}
	}

	ConsumeInputs();
}

FVector2D UFreeCameraInputComponent::GetStrafeInput() const
{
	auto Size2 = StrafeInput.SizeSquared();

	return (Size2 < 1.0f) ? (StrafeInput) : (StrafeInput * FMath::InvSqrt(Size2));
}

void UFreeCameraInputComponent::ConsumeInputs()
{
	StrafeInput = FVector2D::ZeroVector;
	OrbitInput = 0.0f;
	PivotInput = 0.0f;
	DistanceInput = 0.0f;
	bOrbitSnapRight = false;
	bOrbitSnapLeft = false;
}

void UFreeCameraInputComponent::OnForwardInput(float InValue)
{
	StrafeInput.X += InValue;
}

void UFreeCameraInputComponent::OnRightInput(float InValue)
{
	StrafeInput.Y += InValue;
}

void UFreeCameraInputComponent::OnOrbitInput(float InValue)
{
	OrbitInput += InValue;
}

void UFreeCameraInputComponent::OnPivotInput(float InValue)
{
	PivotInput += InValue;
}

void UFreeCameraInputComponent::OnDistanceInput(float InValue)
{
	// Inverted as moving towards the target (positive) reduces its distance from the camera.

	DistanceInput -= InValue;
}

void UFreeCameraInputComponent::OnOrbitSnapRightPressed()
{
	bOrbitSnapRight = bOrbitSnapRightEnabled;
	bOrbitSnapRightEnabled = false;
}

void UFreeCameraInputComponent::OnOrbitSnapLeftPressed()
{
	bOrbitSnapLeft = bOrbitSnapLeftEnabled;
	bOrbitSnapLeftEnabled = false;
}

void UFreeCameraInputComponent::OnOrbitSnapRightReleased()
{
	bOrbitSnapRightEnabled = true;
}

void UFreeCameraInputComponent::OnOrbitSnapLeftReleased()
{
	bOrbitSnapLeftEnabled = true;
}

// ==================================================================== //

