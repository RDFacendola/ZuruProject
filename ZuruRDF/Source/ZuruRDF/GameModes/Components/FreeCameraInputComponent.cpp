
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
}

void UFreeCameraInputComponent::Bind(APawn& InPawn)
{
	FreeCameraComponent = InPawn.FindComponentByClass<UFreeCameraComponent>();
}

void UFreeCameraInputComponent::Advance(float InDeltaSeconds)
{
	if (FreeCameraComponent)
	{
		FreeCameraComponent->OnStrafeInput(StrafeInput);
		FreeCameraComponent->OnOrbitInput(OrbitInput);
		FreeCameraComponent->OnPivotInput(PivotInput);
	}

	ConsumeInputs();
}

FVector2D UFreeCameraInputComponent::GetStrafe() const
{
	auto Size2 = StrafeInput.SizeSquared();

	return (Size2 < 1.0f) ? (StrafeInput) : (StrafeInput * FMath::InvSqrt(Size2));
}

float UFreeCameraInputComponent::GetOrbit() const
{
	return OrbitInput;
}

float UFreeCameraInputComponent::GetPivot() const
{
	return PivotInput;
}

void UFreeCameraInputComponent::ConsumeInputs()
{
	StrafeInput = {};
	OrbitInput = 0.0f;
	PivotInput = 0.0f;
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

// ==================================================================== //

