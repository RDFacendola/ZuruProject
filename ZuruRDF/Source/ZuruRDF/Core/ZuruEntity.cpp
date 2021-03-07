
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
    EntityCollision->SetCollisionObjectType(ECC_GameTraceChannel1);

    SetRootComponent(EntityCollision);
}

void AZuruEntity::SetCollisionBounds(const FBox& InCollisionBounds)
{

}

void AZuruEntity::RegisterGizmo(FZuruGizmo& InGizmo)
{
    Gizmos.AddUnique(&InGizmo);
}

// ==================================================================== //

