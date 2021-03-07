
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
    for (auto&& Entity : Actions.Entities)
    {
        auto EntityPosition2D = Actions.AbsoluteGizmoPosition.Get(FVector2D{ Entity->GetActorLocation() } + Actions.GizmoTranslation);

        auto EntityPosition = FVector{ EntityPosition2D.X, EntityPosition2D.Y, Entity->GetActorLocation().Z };
        auto EntityRotation = Actions.AbsoluteGizmoRotation.Get(Entity->GetActorRotation() + Actions.GizmoRotation);

        Entity->SetActorLocation(EntityPosition, false, nullptr, ETeleportType::ResetPhysics);
        Entity->SetActorRotation(EntityRotation, ETeleportType::ResetPhysics);
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

