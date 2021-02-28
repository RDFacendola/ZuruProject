
// ==================================================================== //

#include "FreeCameraComponent.h"

#include "Math/TranslationMatrix.h"
#include "Math/RotationMatrix.h"

// ==================================================================== //

UFreeCameraComponent::UFreeCameraComponent()
{
	
}

void UFreeCameraComponent::OnStrafeInput(const FVector2D& InStrafe)
{
	// Strafe input is always relative to current rotation.

	auto CurrentRotation = FRotator{ 0.0f, CurrentOrbit, 0.0f };

	auto RelativeStrafe = CurrentRotation.RotateVector(FVector{ InStrafe.X, InStrafe.Y, 0.0f });

	StrafeInput = FVector2D{ RelativeStrafe };
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
	IntegrateInputs(InDeltaTime);
	FilterInputs(InDeltaTime);
	ApplyInputs(InDeltaTime);
}

void UFreeCameraComponent::IntegrateInputs(float InDeltaTime)
{
	// Strafe action quickens as the camera moves away from the target.

	auto StrafeInputWeight = FMath::Lerp(1.0f, MaxDistance / MinDistance, (CurrentDistance - MinDistance) / (MaxDistance - MinDistance));

	TargetLocation += StrafeInputWeight * StrafeInput * StrafeSpeed * InDeltaTime;
	TargetOrbit += OrbitInput * OrbitSpeed * InDeltaTime;
	TargetPivot += PivotInput * PivotSpeed * InDeltaTime;
	TargetDistance += TargetDistance * DistanceInput * DistanceSpeed * InDeltaTime;

	TargetPivot = FMath::Clamp(TargetPivot, MinPivot, MaxPivot);
	TargetDistance = FMath::Clamp(TargetDistance, MinDistance, MaxDistance);
}

void UFreeCameraComponent::FilterInputs(float InDeltaTime)
{
	// Smoothly interpolate the current movements to avoid abrupt camera movements.

	CurrentLocation = FMath::Vector2DInterpTo(CurrentLocation, TargetLocation, InDeltaTime, StrafeSmooth);
	CurrentOrbit = FMath::FInterpTo(CurrentOrbit, TargetOrbit, InDeltaTime, OrbitSmooth);
	CurrentPivot = FMath::FInterpTo(CurrentPivot, TargetPivot, InDeltaTime, PivotSmooth);
	CurrentDistance = FMath::FInterpTo(CurrentDistance, TargetDistance, InDeltaTime, DistanceSmooth);
}

void UFreeCameraComponent::ApplyInputs(float InDeltaTime)
{
	// Update camera component (distance, pivot and vertical offset).

	auto CameraDistanceTransform = FTranslationMatrix{ FVector{ -CurrentDistance, 0.0f, 0.0f } };
	auto CameraPivotTransform = FRotationMatrix{ FRotator{ -CurrentPivot, 0.0f, 0.0f } };
	auto CameraVerticalOffsetTransform = FTranslationMatrix{ FVector{ 0.0f, 0.0f, VerticalOffset } };

	SetRelativeTransform(FTransform{ CameraDistanceTransform * CameraPivotTransform * CameraVerticalOffsetTransform });

	// Update the owning actor or the parent component (strafe and orbit).

	if (bMoveActor)
	{
		auto& Actor = *GetOwner();

		auto ActorLocation = FVector{ CurrentLocation.X, CurrentLocation.Y, Actor.GetActorLocation().Z };
		auto ActorRotation = FRotator{ 0.0f, CurrentOrbit, 0.0f };

		Actor.SetActorLocationAndRotation(ActorLocation, ActorRotation);
	}
	else
	{
		auto& Parent = *GetAttachParent();

		auto ComponentLocation = FVector{ CurrentLocation.X, CurrentLocation.Y, Parent.GetRelativeLocation().Z };
		auto ComponentRotation = FRotator{ 0.0f, CurrentOrbit, 0.0f };

		Parent.SetRelativeLocationAndRotation(ComponentLocation, ComponentRotation);
	}
}

void UFreeCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	auto& Actor = *GetOwner();

	CurrentLocation = FVector2D{ Actor.GetActorLocation() };
	CurrentOrbit = Actor.GetActorRotation().Yaw;
	CurrentPivot = FMath::Clamp(DefaultPivot, MinPivot, MaxPivot);;
	CurrentDistance = FMath::Clamp(DefaultDistance, MinPivot, MaxPivot);;

	TargetLocation = CurrentLocation;
	TargetOrbit = CurrentOrbit;
	TargetPivot = CurrentPivot;
	TargetDistance = CurrentDistance;
}

// ==================================================================== //

