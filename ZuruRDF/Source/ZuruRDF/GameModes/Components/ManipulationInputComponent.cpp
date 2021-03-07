
// ==================================================================== //

#include "ManipulationInputComponent.h"

#include "ZuruRDF/GameModes/Inputs/ManipulationInputs.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

/************************************************************************/
/* MANIPULATION INPUT COMPONENT                                         */
/************************************************************************/

void UManipulationInputComponent::Bind(AGameModeBase& InGameMode)
{
    ManipulationComponent = InGameMode.FindComponentByClass<UManipulationComponent>();
}

void UManipulationInputComponent::Bind(APlayerController& InPlayerController)
{
    InPlayerController.bShowMouseCursor = true;
    
    PlayerController = &InPlayerController;

    GetWidget().Bind(InPlayerController);
    GetGizmo().Bind(InPlayerController);
}

void UManipulationInputComponent::Bind(UInputComponent& InInputComponent)
{
    InInputComponent.BindAction(FManipulationInputs::kManipulationSelect, IE_Pressed, this, &UManipulationInputComponent::OnSelectPressed);
    InInputComponent.BindAction(FManipulationInputs::kManipulationSelect, IE_Released, this, &UManipulationInputComponent::OnSelectReleased);
    InInputComponent.BindAction(FManipulationInputs::kManipulationSelectAdditionalEntity, IE_Pressed, this, &UManipulationInputComponent::OnSelectAdditionalEntityPressed);
    InInputComponent.BindAction(FManipulationInputs::kManipulationSelectAdditionalEntity, IE_Released, this, &UManipulationInputComponent::OnSelectAdditionalEntityReleased);

    GetGizmo().Bind(InInputComponent);
}

void UManipulationInputComponent::Bind(APawn& InPawn)
{
    Pawn = &InPawn;

    GetWidget().Bind(InPawn);
}

void UManipulationInputComponent::Advance(float InDeltaSeconds)
{
    // Send the action to the component.

    auto& GizmoActions = GetGizmo().GetActions();

    Actions.ActiveGizmo = GizmoActions.ActiveGizmo;
    Actions.AbsolutePosition = GizmoActions.AbsolutePosition;
    Actions.AbsoluteRotation = GizmoActions.AbsoluteRotation;

    // IMPORTANT: This component only exists on the server! This method has to replicate the actions
    //            on the remote ManipulationInputComponent and apply them there (and wait for synchronization
    //            to see those actions replicated on the clients).

    ManipulationComponent->SetActions(Actions);

    // Consume the inputs.

    GetGizmo().ConsumeActions();

    Actions.ActiveGizmo = nullptr;
    Actions.AbsolutePosition = TOptional<FVector2D>{};
    Actions.AbsoluteRotation = TOptional<FRotator>{};

    // Update the gizmo status.
    // NOTE: This is not particularly efficient, but we don't expect hundreds of entities being moved around.

    // GetGizmo().SelectEntities(Actions.Entities);

    GetGizmo().Advance(InDeltaSeconds);
}

void UManipulationInputComponent::OnSelectPressed()
{
    if (bSelectEnabled)
    {
        bSelectEnabled = false;

        // Gizmo interaction starts with a click on a gizmo component
        // and has precedence over entity selection.
        // If no gizmo was hit, check whether a new entity is being selected.

        if (!GetGizmo().ConditionalActivateGizmo())
        {
            Actions.Entities.Reset();

            GetWidget().ClearSelection();

            GetGizmo().SelectEntities({});

            SelectAdditionalEntity();
        }
    }
}

void UManipulationInputComponent::OnSelectReleased()
{
    bSelectEnabled = true;

    GetGizmo().DeactivateGizmo();
}

void UManipulationInputComponent::OnSelectAdditionalEntityPressed()
{
    if (bSelectAdditionalEntityEnabled)
    {
        bSelectAdditionalEntityEnabled = false;

        GetGizmo().DeactivateGizmo();

        SelectAdditionalEntity();
    }
}

void UManipulationInputComponent::OnSelectAdditionalEntityReleased()
{
    bSelectAdditionalEntityEnabled = true;
}

void UManipulationInputComponent::OnSpawnTableClicked()
{
    SpawnEntity(TEXT("TABLE"));
}

void UManipulationInputComponent::OnSpawnChairClicked()
{
    SpawnEntity(TEXT("CHAIR"));
}

void UManipulationInputComponent::SelectAdditionalEntity()
{
    auto HitResult = FHitResult{};

    if (PlayerController->GetHitResultUnderCursorForObjects({ EntityObjectType }, false, HitResult))
    {
        if (auto ZuruEntity = Cast<AZuruEntity>(HitResult.Actor.Get()))
        {
            if (!Actions.Entities.Contains(ZuruEntity))
            {
                // Select the entity.

                Actions.Entities.Add(ZuruEntity);

                GetWidget().SelectEntity(*ZuruEntity);
            }
            else
            {
                // Deselect the entity.

                Actions.Entities.Remove(ZuruEntity);

                GetWidget().DeselectEntity(*ZuruEntity);
            }
        }

        // Update the gizmo status for the current selection set.

        GetGizmo().SelectEntities(Actions.Entities);
    }
}

void UManipulationInputComponent::OnWidgetConstructed()
{
    // Bind to widget inputs.

    Widget->OnSpawnTableClicked().AddDynamic(this, &UManipulationInputComponent::OnSpawnTableClicked);
    Widget->OnSpawnChairClicked().AddDynamic(this, &UManipulationInputComponent::OnSpawnChairClicked);
}

UManipulationWidget& UManipulationInputComponent::GetWidget()
{
    if (!Widget)
    {
        auto WidgetConcreteClass = WidgetClass ? WidgetClass : UManipulationWidget::StaticClass();

        Widget = CreateWidget<UManipulationWidget>(GetWorld(), WidgetConcreteClass);

        Widget->OnConstructed.AddDynamic(this, &UManipulationInputComponent::OnWidgetConstructed);
    }

    return *Widget;
}

AManipulationGizmo& UManipulationInputComponent::GetGizmo()
{
    if (!Gizmo)
    {
        auto GizmoConcreteClass = GizmoClass ? GizmoClass : AManipulationGizmo::StaticClass();

        auto SpawnParameters = FActorSpawnParameters{};

        SpawnParameters.bNoFail = true;

        Gizmo = GetWorld()->SpawnActor<AManipulationGizmo>(GizmoConcreteClass, FTransform::Identity, SpawnParameters);
    }

    return *Gizmo;
}

void UManipulationInputComponent::SpawnEntity(const FName& InEntityKey)
{
    SpawnEntityAt(InEntityKey, Pawn->GetActorTransform());
}

void UManipulationInputComponent::SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform)
{
    if (ManipulationComponent)
    {
        ManipulationComponent->SpawnEntityAt(InEntityKey, InEntityTransform);
    }
}

// ==================================================================== //

PRAGMA_ENABLE_OPTIMIZATION