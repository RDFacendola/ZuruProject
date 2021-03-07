
// ==================================================================== //

#include "ManipulationComponent.h"

#include "ZuruRDF/Core/ZuruGameInstance.h"
#include "ZuruRDF/Core/ZuruEntity.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION COMPONENT                                               */
/************************************************************************/

void UManipulationComponent::Bind(AGameStateBase& InGameState)
{
    ProjectComponent = InGameState.FindComponentByClass<UProjectComponent>();
}

void UManipulationComponent::SetActions(const FManipulationActions& InActions)
{
    Actions = InActions;
}

void UManipulationComponent::Advance(float InDeltaTime)
{
    if (Actions.ActiveGizmo)
    {
        if (Actions.ActiveGizmo->GetEntityGizmo())
        {
            // Search the entity the gizmo belongs to and update it.

            for (auto&& Entity : Actions.Entities)
            {
                Entity->UpdateGizmo(*Actions.ActiveGizmo->GetEntityGizmo(), Actions.GizmoTranslation, Actions.GizmoRotation);
            }
        }
        else
        {
            // Unbound gizmos move the entity around.

            for (auto&& Entity : Actions.Entities)
            {
                auto EntityPosition = Entity->GetActorLocation() + FVector{ Actions.GizmoTranslation.X, Actions.GizmoTranslation.Y, 0.0f };
                auto EntityRotation = Entity->GetActorRotation() + Actions.GizmoRotation;

                Entity->SetActorLocation(EntityPosition, false, nullptr, ETeleportType::ResetPhysics);
                Entity->SetActorRotation(EntityRotation, ETeleportType::ResetPhysics);
            }

            Actions = {};
        }
    }
}

void UManipulationComponent::SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform)
{
    if (ProjectComponent)
    {
        ProjectComponent->SpawnEntityAt(InEntityKey, InEntityTransform);
    }
}

// ==================================================================== //

