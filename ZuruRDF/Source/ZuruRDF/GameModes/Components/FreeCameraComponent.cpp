
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

	TargetLocation += StrafeInput * StrafeSpeed * InDeltaTime;
	TargetOrbit += OrbitInput * OrbitSpeed * InDeltaTime;
	TargetPivot += PivotInput * PivotSpeed * InDeltaTime;
	TargetDistance += TargetDistance * DistanceInput * DistanceSpeed * InDeltaTime;

	TargetPivot = FMath::Clamp(TargetPivot, MinPivot, MaxPivot);
	TargetDistance = FMath::Clamp(TargetDistance, MinDistance, MaxDistance);

	// Smoothly move towards target values.

	auto InvDeltaTime = 1.0f / InDeltaTime;

	//Location = FMath::Lerp(TargetLocation, Location, StrafeSmooth * InvDeltaTime);
	//Orbit = FMath::Lerp(TargetOrbit, Orbit, OrbitSmooth * InvDeltaTime);
	//Pivot = FMath::Lerp(TargetPivot, Pivot, PivotSmooth * InvDeltaTime);
	Distance = FMath::Lerp(TargetDistance, Distance, FMath::Clamp(DistanceSmooth * InDeltaTime, 0.0f, 1.0f));

	// Update camera distance and vertical offset.

	SetRelativeLocation(FVector{ -Distance, 0.0f, VerticalOffset });
}

void UFreeCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	Distance = FMath::Clamp(Distance, MinDistance, MaxDistance);
	TargetDistance = Distance;
}

// ==================================================================== //

