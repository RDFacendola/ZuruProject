
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "ZuruEntity.generated.h"

// ==================================================================== //

/************************************************************************/
/* ZURU ENTITY                                                          */
/************************************************************************/

// Represents a physical object in the project.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Entites)
class ZURURDF_API AZuruEntity: public AActor
{
    GENERATED_BODY()
    
public:

    // Create a new entity.
    AZuruEntity();

protected:

    // Set the entity collision bounds.
    void SetCollisionBounds(const FBox& InCollisionBounds);

private:

    // Entity collision bounds.
    UPROPERTY(Category = Components, DisplayName = Entity, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* EntityCollision{ nullptr };

};

// ==================================================================== //
