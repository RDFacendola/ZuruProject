
// ==================================================================== //

#include "ProceduralGizmo.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GIZMO                                                     */
/************************************************************************/

FProceduralGizmo::FProceduralGizmo(const FTransform& InBasis0, const FTransform& InBasis1)
	: TransformBasis0(InBasis0)
	, TransformBasis1(InBasis1)
{
	// Set the initial gizmo value to 0.5 on each component.

	auto Translation0 = TransformBasis0.GetTranslation();
	auto Translation1 = TransformBasis1.GetTranslation();

	auto Rotation0 = TransformBasis0.GetRotation().Euler();
	auto Rotation1 = TransformBasis1.GetRotation().Euler();

	auto Scale0 = TransformBasis0.GetScale3D();
	auto Scale1 = TransformBasis1.GetScale3D();

	auto Translation = FMath::Lerp(Translation0, Translation1, 0.5f);
	auto Rotation = FRotator::MakeFromEuler(FMath::Lerp(Rotation0, Rotation1, 0.5f));
	auto Scale = FMath::Lerp(Scale0, Scale1, 0.5f);

	Transform.SetComponents(Rotation.Quaternion(), Translation, Scale);
}

FVector FProceduralGizmo::GetTranslationWeight() const
{
	auto Translation = Transform.GetTranslation();
	auto Translation0 = TransformBasis0.GetTranslation();
	auto Translation1 = TransformBasis1.GetTranslation();

	auto Weight = (Translation - Translation0) / (Translation1 - Translation0);

	return Weight;
}

FVector FProceduralGizmo::GetRotationWeight() const
{
	auto Rotation = Transform.GetRotation().Euler();
	auto Rotation0 = TransformBasis0.GetRotation().Euler();
	auto Rotation1 = TransformBasis1.GetRotation().Euler();

	auto RotationDelta = (Rotation - Rotation0);
	auto RotationRange = (Rotation1 - Rotation0);

	auto Weight = (Rotation - Rotation0) / (Rotation1 - Rotation0);

	return Weight;
}

FVector FProceduralGizmo::GetScaleWeight() const
{
	auto Scale = Transform.GetScale3D();
	auto Scale0 = TransformBasis0.GetScale3D();
	auto Scale1 = TransformBasis1.GetScale3D();

	auto Weight = (Scale - Scale0) / (Scale1 - Scale0);

	return Weight;
}

const FTransform& FProceduralGizmo::GetTransform() const
{
	return Transform;
}

void FProceduralGizmo::SetTransform(const FTransform& InTransform)
{
	//

	auto Translation = InTransform.GetTranslation();
	auto Translation0 = TransformBasis0.GetTranslation();
	auto Translation1 = TransformBasis1.GetTranslation();

	auto Rotation = InTransform.GetRotation().Euler();
	auto Rotation0 = TransformBasis0.GetRotation().Euler();
	auto Rotation1 = TransformBasis1.GetRotation().Euler();

	auto Scale = InTransform.GetScale3D();
	auto Scale0 = TransformBasis0.GetScale3D();
	auto Scale1 = TransformBasis1.GetScale3D();

	// Sort ranges.

	auto MinTranslation = Translation0.ComponentMin(Translation1);
	auto MaxTranslation = Translation0.ComponentMax(Translation1);

	auto MinRotation = Rotation0.ComponentMin(Rotation1);
	auto MaxRotation = Rotation0.ComponentMax(Rotation1);

	auto MinScale = Scale0.ComponentMin(Scale1);
	auto MaxScale = Scale0.ComponentMax(Scale1);

	// Clamp.
	
	auto ClampVector = [](const auto& InVector, const auto& InMin, const auto& InMax)
	{
		return FVector
		{
			FMath::Clamp(InVector.X, InMin.X, InMax.X),
			FMath::Clamp(InVector.Y, InMin.Y, InMax.Y),
			FMath::Clamp(InVector.Z, InMin.Z, InMax.Z)
		};
	};

	auto ClampedTranslation = ClampVector(Translation, MinTranslation, MaxTranslation);
	auto ClampedRotation = FRotator::MakeFromEuler(ClampVector(Rotation, MinRotation, MaxRotation));
	auto ClampedScale = ClampVector(Scale, MinScale, MaxScale);

	Transform.SetComponents(ClampedRotation.Quaternion(), ClampedTranslation, ClampedScale);
}

// ==================================================================== //

