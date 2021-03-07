
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
                // Entity->UpdateGizmo(*Actions.ActiveGizmo->GetEntityGizmo(), Actions.GizmoTranslation, Actions.GizmoRotation);
            }
        }
        else
        {
            // Update entity position.

            if (Actions.AbsolutePosition.IsSet())
            {
                for (auto&& Entity : Actions.Entities)
                {
                    auto EntityLocation2D = Actions.AbsolutePosition.GetValue();
                    auto EntityLocation3D = Entity->GetActorLocation();

                    Entity->SetActorLocation(FVector{ EntityLocation2D.X, EntityLocation2D.Y, EntityLocation3D.Z });
                }
            }

            // Update entity rotation.

            if (Actions.AbsoluteRotation.IsSet())
            {
                for (auto&& Entity : Actions.Entities)
                {
                    auto EntityRotation2D = Actions.AbsoluteRotation.GetValue();
                    auto EntityRotation3D = Entity->GetActorRotation();

                    Entity->SetActorRotation(FRotator{ EntityRotation3D.Pitch, EntityRotation2D.Yaw, EntityRotation3D.Roll });
                }
            }
        }
    }

    Actions = {};
}

void UManipulationComponent::SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform)
{
    if (ProjectComponent)
    {
        ProjectComponent->SpawnEntityAt(InEntityKey, InEntityTransform);
    }
}

// ==================================================================== //

