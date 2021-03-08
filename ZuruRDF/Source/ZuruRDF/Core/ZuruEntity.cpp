
// ==================================================================== //

#include "ZuruEntity.h"

// ==================================================================== //

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

