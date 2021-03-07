
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "ZuruGizmo.h"

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

    // Execute a function on each gizmo owned by the entity.
    template <typename TFunction>
    void ForEachGizmo(TFunction&& InFunction);

    // Execute a function on each gizmo owned by the entity.
    template <typename TFunction>
    void ForEachGizmo(TFunction&& InFunction) const;

protected:

    // Set the entity collision bounds.
    void SetCollisionBounds(const FBox& InCollisionBounds);

    // Register a gizmo to the entity.
    void RegisterGizmo(FZuruGizmo& InGizmo);

private:

    // Entity collision bounds.
    UPROPERTY(Category = Components, DisplayName = Entity, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UBoxComponent* EntityCollision{ nullptr };

    // Entity gizmos, used to drive procedural mesh generation.
    TArray<FZuruGizmo*> Gizmos;

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

template <typename TFunction>
inline void AZuruEntity::ForEachGizmo(TFunction&& InFunction)
{
    for (auto&& Gizmo : Gizmos)
    {
        InFunction(*Gizmo);
    }
}

template <typename TFunction>
inline void AZuruEntity::ForEachGizmo(TFunction&& InFunction) const
{
    for (auto&& Gizmo : Gizmos)
    {
        InFunction(static_cast<const FZuruGizmo&>(*Gizmo));
    }
}
// ==================================================================== //

