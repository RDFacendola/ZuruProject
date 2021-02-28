
// ==================================================================== //

#include "FreeCameraComponent.h"

// ==================================================================== //

UFreeCameraComponent::UFreeCameraComponent()
{
	
}

void UFreeCameraComponent::OnStrafeInput(const FVector2D& InStrafe)
{
	StrafeInput = InStrafe;
}

void UFreeCameraComponent::OnOrbitInput(float InOrbit)
{
	OrbitInput = InOrbit;
}

void UFreeCameraComponent::OnPivotInput(float InPivot)
{
	PivotInput = InPivot;
}

void UFreeCameraComponent::OnDistanceInput(float InDistance)
{
	DistanceInput = InDistance;
}

void UFreeCameraComponent::Advance(float InDeltaTime)
{
	// Evaluate movement from input.

	auto NormalizedStrafeInput = StrafeInput.GetSafeNormal() * (StrafeInput.X + StrafeInput.Y - StrafeInput.X * StrafeInput.Y);		// Probabilistic sum to preserve "analog" inputs.

	TargetLocation += NormalizedStrafeInput * StrafeSpeed * InDeltaTime;
	TargetOrbit += OrbitInput * OrbitSpeed * InDeltaTime;
	TargetPivot += PivotInput * PivotSpeed * InDeltaTime;
	TargetDistance += DistanceInput * DistanceSpeed * InDeltaTime;
	TargetPivot = FMath::Clamp(TargetPivot, kMinPivot, kMaxPivot);

	// Smoothly move towards target values.

	auto InvDeltaTime = 1.0f / InDeltaTime;

	//Location = FMath::Lerp(TargetLocation, Location, StrafeSmooth * InvDeltaTime);
	//Orbit = FMath::Lerp(TargetOrbit, Orbit, OrbitSmooth * InvDeltaTime);
	//Pivot = FMath::Lerp(TargetPivot, Pivot, PivotSmooth * InvDeltaTime);
	Distance = FMath::Lerp(TargetDistance, Distance, DistanceSmooth * InDeltaTime);

	// Update camera distance and vertical offset.

	SetRelativeLocation(FVector{ -Distance, 0.0f, VerticalOffset });
}

void UFreeCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetDistance = Distance;
}

// ==================================================================== //

