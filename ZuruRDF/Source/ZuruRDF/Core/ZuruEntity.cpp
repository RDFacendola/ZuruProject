
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

FZuruGizmo*AZuruEntity::GetGizmo(int32 InIndex)
{
    return nullptr;
}

// ==================================================================== //

