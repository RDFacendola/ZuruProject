
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
UCLASS(Blueprintable, BlueprintType, ClassGroup = Entities)
class ZURURDF_API AZuruEntity: public AActor
{
    GENERATED_BODY()
    
public:

    // Create a new entity.
    AZuruEntity();

    // (Re)generate entity geometry.
    virtual void Generate();

    // Execute a function on each component of type TComponent owned by the entity.
    template <typename TComponent, typename TFunction>
    void ForEach(TFunction&& InFunction);

    // Execute a function on each gizmo owned by the entity.
    template <typename TFunction>
    void ForEachGizmo(TFunction&& InFunction);

    // Get the number of gizmos on this entity.
    virtual int32 GetNumGizmos() const;

    // Get a gizmo on this entity by index. If no such gizmo exists return nullptr.
    virtual FZuruGizmo* GetGizmo(int32 InIndex);

    // Set a gizmo location, in world space.
    virtual void SetGizmoLocation(int32 InGizmoIndex, const FVector2D& InLocationWS);

    // Set a gizmo rotation, in world space.
    virtual void SetGizmoRotation(int32 InGizmoIndex, const FRotator& InRotationWS);

    void PostInitProperties() override;

protected:

    // Set the entity collision bounds.
    void SetCollisionBounds(const FBox& InCollisionBounds);

private:

    // Object type used to filter out entities.
    UPROPERTY(EditAnywhere, Category = Input)
    TEnumAsByte<EObjectTypeQuery> EntityObjectType{ EObjectTypeQuery::ObjectTypeQuery1 };

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

template <typename TFunction>
inline void AZuruEntity::ForEachGizmo(TFunction&& InFunction)
{
    for (auto&& Gizmo : Gizmos)
    {
        InFunction(*Gizmo);
    }
}

// ==================================================================== //

