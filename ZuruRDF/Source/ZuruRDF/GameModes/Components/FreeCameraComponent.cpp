
// ==================================================================== //

#include "FreeCameraComponent.h"

#include "Math/TranslationMatrix.h"
#include "Math/RotationMatrix.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

UFreeCameraComponent::UFreeCameraComponent()
{
	
}

void UFreeCameraComponent::SetActions(const FFreeCameraActions& InCameraActions)
{
	Actions = InCameraActions;
}

void UFreeCameraComponent::Advance(float InDeltaTime)
{
	IntegrateActions(InDeltaTime);
	ApplyActions(InDeltaTime);

	Actions = {};
}

FVector UFreeCameraComponent::GetLocation() const
{
	return (bTargetRoot) ? (GetOwner()->GetActorLocation()) : (GetAttachParent()->GetComponentLocation());
}

FVector2D UFreeCameraComponent::GetLocation2D() const
{
	return FVector2D{ GetLocation() };
}

FRotator UFreeCameraComponent::GetOrbit() const
{
	return (bTargetRoot) ? (GetOwner()->GetActorRotation()) : (GetAttachParent()->GetComponentRotation());
}

float UFreeCameraComponent::GetPivot() const
{
	return -GetRelativeRotation().Pitch;
}

float UFreeCameraComponent::GetDistance() const
{
	return FVector::Distance(GetLocation() + VerticalOffset * FVector::UpVector , GetComponentLocation());
}

void UFreeCameraComponent::IntegrateActions(float InDeltaTime)
{
	// Strafe action.

	auto StrafeWS = [&]()
	{
		// From local space to world space, clamping the combined input.

		auto Size2 = Actions.Strafe.SizeSquared();

		auto StrafeLS = (Size2 < 1.0f) ? (Actions.Strafe) : (Actions.Strafe * FMath::InvSqrt(Size2));

		return Actions.Strafe.GetRotated(GetOrbit().Yaw);
	}();
	
	auto StrafeSpeedup = FMath::Lerp(1.0f, MaxDistance / MinDistance, (GetDistance() - MinDistance) / (MaxDistance - MinDistance));		// Increase the speed when far away from the target and cover more space.

	TargetLocation += StrafeSpeedup * StrafeWS * StrafeSpeed * InDeltaTime;

	// Distance action.

	auto DistanceSpeedup = TargetDistance;

	TargetDistance += DistanceSpeedup * Actions.Distance * DistanceSpeed * InDeltaTime;

	TargetDistance = FMath::Clamp(TargetDistance, MinDistance, MaxDistance);

	// Clockwise and CounterClockwise actions are mutually exclusive with the Orbit action.

	if (Actions.bClockwise)
	{
		TargetOrbit.Yaw = FMath::FloorToInt(TargetOrbit.Yaw / 90.0f) * 90.0f - 90.0f;		// Snap and rotate clockwise.
	}
	else if (Actions.bCounterClockwise)
	{
		TargetOrbit.Yaw = FMath::CeilToInt(TargetOrbit.Yaw / 90.0f) * 90.0f + 90.0f;		// Snap and rotate counter-clockwise.
	}
	else
	{
		TargetOrbit.Yaw += Actions.Orbit * OrbitSpeed * InDeltaTime;
	}

	TargetOrbit.Normalize();

	// TopView and FrontView actions are mutually exclusive with the Pivot action.

	if (Actions.bTopView)
	{
		TargetPivot = 90.0f;
	}
	else if (Actions.bFrontView)
	{
		TargetPivot = 0.0f;
	}
	else
	{
		TargetPivot += Actions.Pivot * PivotSpeed * InDeltaTime;

		TargetPivot = FMath::Clamp(TargetPivot, MinPivot, MaxPivot);
	}
}

void UFreeCameraComponent::ApplyActions(float InDeltaTime)
{
	// Smoothly interpolate the current actions to avoid abrupt camera movements.

	auto Location = FMath::Vector2DInterpTo(GetLocation2D(), TargetLocation, InDeltaTime, StrafeSmooth);
	auto Orbit  = FMath::RInterpTo(GetOrbit(), TargetOrbit, InDeltaTime, OrbitSmooth);
	auto Pivot = FMath::FInterpTo(GetPivot(), TargetPivot, InDeltaTime, PivotSmooth);
	auto Distance = FMath::FInterpTo(GetDistance(), TargetDistance, InDeltaTime, DistanceSmooth);

	// Update camera component to reflect distance, pivot and vertical offset actions.

	auto DistanceTransform = FTranslationMatrix{ FVector{ -Distance, 0.0f, 0.0f } };
	auto PivotTransform = FRotationMatrix{ FRotator{ -Pivot, 0.0f, 0.0f } };
	auto VerticalOffsetTransform = FTranslationMatrix{ VerticalOffset * FVector::UpVector };

	SetRelativeTransform(FTransform{ DistanceTransform * PivotTransform * VerticalOffsetTransform });

	// Update the target location and rotation to reflect strafe and orbit actions.

	if (bTargetRoot)
	{
		auto& Actor = *GetOwner();

		auto ActorLocation = FVector{ Location.X, Location.Y, Actor.GetActorLocation().Z };
		auto ActorRotation = Orbit;

		Actor.SetActorLocationAndRotation(ActorLocation, ActorRotation);
	}
	else
	{
		auto& Parent = *GetAttachParent();

		auto ComponentLocation = FVector{ Location.X, Location.Y, Parent.GetRelativeLocation().Z };
		auto ComponentRotation = Orbit;

		Parent.SetRelativeLocationAndRotation(ComponentLocation, ComponentRotation);
	}
}

void UFreeCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	auto& Actor = *GetOwner();

	TargetLocation = GetLocation2D();
	TargetOrbit = GetOrbit();
	TargetPivot = GetPivot();
	TargetDistance = GetDistance();
}

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //

