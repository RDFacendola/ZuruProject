
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameStateBase.h"

#include "ZuruRDF/Core/ZuruGizmoComponent.h"

#include "FreeCameraComponent.h"
#include "ProjectComponent.h"

#include "ManipulationComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION ACTIONS                                                 */
/************************************************************************/

// Set of manipulation actions.
//
// @author Raffaele D. Facendola - March 2021.
struct FManipulationActions
{
    // Entities these actions refer to.
    TSet<AZuruEntity*> Entities;

    // Active gizmo.
    UZuruGizmoComponent* ActiveGizmo;

    // Gizmo translation.
    FVector2D GizmoTranslation{ FVector2D::ZeroVector };

    // Gizmo rotation.
    FRotator GizmoRotation{ FRotator::ZeroRotator };

    // Absolute gizmo position.
    TOptional<FVector2D> AbsoluteGizmoPosition{};

    // Absolute gizmo rotation.
    TOptional<FRotator> AbsoluteGizmoRotation{};
};

/************************************************************************/
/* MANIPULATION COMPONENT                                               */
/************************************************************************/

// A component used to handle entity-manipulation-related actions.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS()
class ZURURDF_API UManipulationComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    // Bind the component to a game state.
    void Bind(AGameStateBase& InGameState);

    // Set manipulation actions.
    void SetActions(const FManipulationActions& InActions);

    // Advance the component status.
    void Advance(float InDeltaTime);

    // Spawn an entity by key at given coordinates.
    void SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform);

private:

    // The project the entities manipulated by this component exist into.
    UPROPERTY()
    UProjectComponent* ProjectComponent{ nullptr };

    // Pending actions.
    FManipulationActions Actions;

};

// ==================================================================== //
