
// ==================================================================== //

#include "FreeCameraComponent.h"
#include "CameraInputs.h"

// ==================================================================== //

void UFreeCameraComponent::Bind(UInputComponent& InInputComponent)
{
	InInputComponent.BindAxis(FCameraInputs::kCameraForward, this, &UFreeCameraComponent::OnForwardInput);
	InInputComponent.BindAxis(FCameraInputs::kCameraRight, this, &UFreeCameraComponent::OnRightInput);
	InInputComponent.BindAxis(FCameraInputs::kCameraOrbit, this, &UFreeCameraComponent::OnOrbitInput);
	InInputComponent.BindAxis(FCameraInputs::kCameraPivot, this, &UFreeCameraComponent::OnPivotInput);
}

void UFreeCameraComponent::SetLocation(const FVector2D& InLocation)
{
	Location = InLocation;
	TargetLocation = Location;
}

void UFreeCameraComponent::SetOrbit(float InOrbit)
{
	Orbit = InOrbit;
	TargetOrbit = Orbit;
}

void UFreeCameraComponent::SetPivot(float InPivot)
{
	Pivot = FMath::Clamp(InPivot, kMinPivot, kMaxPivot);
	TargetPivot = Pivot;
}

const FVector2D& UFreeCameraComponent::GetLocation() const
{
	return Location;
}

float UFreeCameraComponent::GetOrbit() const
{
	return Orbit;
}

float UFreeCameraComponent::GetPivot() const
{
	return Pivot;
}

void UFreeCameraComponent::TickComponent(float InDeltaTime, enum ELevelTick InTickType, FActorComponentTickFunction* InTickFunction)
{
	Super::TickComponent(InDeltaTime, InTickType, InTickFunction);

	// Evaluate movement from input.

	auto NormalizedStrafeInput = StrafeInput.GetSafeNormal() * (StrafeInput.X + StrafeInput.Y - StrafeInput.X * StrafeInput.Y);		// Probabilistic sum to preserve "analog" inputs.

	TargetLocation += NormalizedStrafeInput * StrafeSpeed * InDeltaTime;
	TargetOrbit += OrbitInput * OrbitSpeed * InDeltaTime;
	TargetPivot += PivotInput * PivotSpeed * InDeltaTime;

	TargetPivot = FMath::Clamp(TargetPivot, kMinPivot, kMaxPivot);

	// Smoothly move towards target values.

	auto InvDeltaTime = 1.0f / InDeltaTime;

	Location = FMath::Lerp(TargetLocation, Location, StrafeSmooth * InvDeltaTime);
	Orbit = FMath::Lerp(TargetOrbit, Orbit, OrbitSmooth * InvDeltaTime);
	Pivot = FMath::Lerp(TargetPivot, Pivot, PivotSmooth * InvDeltaTime);

	// Consume the input.

	StrafeInput = {};
	OrbitInput = 0.0f;
	PivotInput = 0.0f;

}

void UFreeCameraComponent::OnForwardInput(float InValue)
{
	StrafeInput.X += InValue;
}

void UFreeCameraComponent::OnRightInput(float InValue)
{
	StrafeInput.Y += InValue;
}

void UFreeCameraComponent::OnOrbitInput(float InValue)
{
	OrbitInput += InValue;
}

void UFreeCameraComponent::OnPivotInput(float InValue)
{
	PivotInput += InValue;
}

// ==================================================================== //

