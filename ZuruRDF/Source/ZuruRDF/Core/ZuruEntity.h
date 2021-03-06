
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

    // Execute a function on each component of type TComponent owned by the entity.
    template <typename TComponent, typename TFunction>
    void ForEach(TFunction&& InFunction);

protected:

    // Set the entity collision bounds.
    void SetCollisionBounds(const FBox& InCollisionBounds);

private:

    // Entity collision bounds.
    UPROPERTY(Category = Components, DisplayName = Entity, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* EntityCollision{ nullptr };

};

// ==================================================================== //

/************************************************************************/
/* IMPLEMENTATION                                                       */
/************************************************************************/

// ZuruEntity.
// ===========

template <typename TComponent, typename TFunction>
inline void AZuruEntity::ForEach(TFunction&& InFunction)
{
    for (auto&& EntityComponent : GetComponents())
    {
        if (auto PrimitiveComponent = Cast<TComponent>(EntityComponent))
        {
            InFunction(*PrimitiveComponent);
        }
    }
}

// ==================================================================== //

