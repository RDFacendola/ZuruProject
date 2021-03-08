
// ==================================================================== //

#include "ZuruEntity.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

/************************************************************************/
/* ZURU ENTITY                                                          */
/************************************************************************/

AZuruEntity::AZuruEntity()
{
    EntityCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ChairRoot"));

    EntityCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    SetRootComponent(EntityCollision);
}

void AZuruEntity::Generate()
{

}

void AZuruEntity::PostInitProperties()
{
    Super::PostInitProperties();

    auto CollisionChannel = UEngineTypes::ConvertToCollisionChannel(EntityObjectType);

    EntityCollision->SetCollisionObjectType(CollisionChannel);
}

void AZuruEntity::SetCollisionBounds(const FBox& InCollisionBounds)
{
    // The entity collision is centered on the entity, so it has to be symmetric.

    auto MaxX = FMath::Max(FMath::Abs(InCollisionBounds.Min.X), FMath::Abs(InCollisionBounds.Max.X));
    auto MaxY = FMath::Max(FMath::Abs(InCollisionBounds.Min.Y), FMath::Abs(InCollisionBounds.Max.Y));
    auto MaxZ = FMath::Max(FMath::Abs(InCollisionBounds.Min.Z), FMath::Abs(InCollisionBounds.Max.Z));

    EntityCollision->SetBoxExtent(FVector{ MaxX, MaxY, MaxZ });
}

int32 AZuruEntity::GetNumGizmos() const
{
    return 0;
}

FZuruGizmo* AZuruEntity::GetGizmo(int32 InIndex)
{
    return nullptr;
}

void AZuruEntity::SetGizmoLocation(int32 InGizmoIndex, const FVector2D& InLocationWS)
{
    // To be defined in derived classes.
}

void AZuruEntity::SetGizmoRotation(int32 InGizmoIndex, const FRotator& InRotationWS)
{
    // To be defined in derived classes.
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION
