
// ==================================================================== //

#include "ZuruGizmo.h"

// ==================================================================== //

/************************************************************************/
/* ZURU GIZMO                                                           */
/************************************************************************/

FZuruGizmo::FZuruGizmo()
{

}

FZuruGizmo::FZuruGizmo(TranslationTag, const FVector& InTranslation0, const FVector& InTranslation1, const FVector& InWeight)
    : Translation0(InTranslation0)
    , Translation1(InTranslation1)
{
    SetTranslationWeight(InWeight);
}

FZuruGizmo::FZuruGizmo(RotationTag, const FVector& InRotation0, const FVector& InRotation1, const FVector& InWeight)
    : Rotation0(InRotation0)
    , Rotation1(InRotation1)
{
    SetRotationWeight(InWeight);
}

FZuruGizmo::FZuruGizmo(ScaleTag, const FVector& InScale0, const FVector& InScale1, const FVector& InWeight)
    : Scale0(InScale0)
    , Scale1(InScale1)
{
    SetScaleWeight(InWeight);
}

void FZuruGizmo::SetTranslationWeight(const FVector& InWeight)
{
    Translation = GetTransform(Translation0, Translation1, InWeight);
}

void FZuruGizmo::SetRotationWeight(const FVector& InWeight)
{
    Rotation = GetTransform(Rotation0, Rotation1, InWeight);
}

void FZuruGizmo::SetScaleWeight(const FVector& InWeight)
{
    Scale = GetTransform(Scale0, Scale1, InWeight);
}

FVector FZuruGizmo::GetTranslationWeight() const
{
    return GetWeight(Translation0, Translation1, Translation);
}

FVector FZuruGizmo::GetRotationWeight() const
{
    return GetWeight(Rotation0, Rotation1, Rotation);
}

FVector FZuruGizmo::GetScaleWeight() const
{
    return GetWeight(Scale0, Scale1, Scale);
}

FVector FZuruGizmo::GetTransform(const FVector& InBase0, const FVector& InBase1, const FVector& InWeight) const
{
    return
    {
        FMath::Lerp(InBase0.X, InBase1.X, FMath::Clamp(InWeight.X, 0.0f, 1.0f)),
        FMath::Lerp(InBase0.Y, InBase1.Y, FMath::Clamp(InWeight.Y, 0.0f, 1.0f)),
        FMath::Lerp(InBase0.Z, InBase1.Z, FMath::Clamp(InWeight.Z, 0.0f, 1.0f))
    };
}

FVector FZuruGizmo::GetWeight(const FVector& InBase0, const FVector& InBase1, const FVector& InTransform) const
{
    auto Range = InBase1 - InBase0;

    return
    {
        FMath::Clamp(((Range.X > 0.0f) ? ((InTransform.X - InBase0.X) / Range.X) : 0.5f), 0.0f, 1.0f),
        FMath::Clamp(((Range.Y > 0.0f) ? ((InTransform.Y - InBase0.Y) / Range.Y) : 0.5f), 0.0f, 1.0f),
        FMath::Clamp(((Range.Z > 0.0f) ? ((InTransform.Z - InBase0.Z) / Range.Z) : 0.5f), 0.0f, 1.0f)
    };
}

// ==================================================================== //

