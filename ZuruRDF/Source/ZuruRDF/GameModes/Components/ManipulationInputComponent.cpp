
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
    auto& Actions = GetGizmo().GetActions();

    // Send gizmo actions over.

    GetGizmo().ConsumeActions();
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
            SelectedEntities.Reset();

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
            if (!SelectedEntities.Contains(ZuruEntity))
            {
                // Select the entity.

                SelectedEntities.Add(ZuruEntity);

                GetWidget().SelectEntity(*ZuruEntity);
            }
            else
            {
                // Deselect the entity.

                SelectedEntities.Remove(ZuruEntity);

                GetWidget().DeselectEntity(*ZuruEntity);
            }
        }

        // Update the gizmo status for the current selection set.

        GetGizmo().SelectEntities(SelectedEntities);
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