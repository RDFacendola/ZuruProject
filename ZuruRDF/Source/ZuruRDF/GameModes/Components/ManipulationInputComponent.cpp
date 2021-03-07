
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
}

void UManipulationInputComponent::Bind(UInputComponent& InInputComponent)
{
    InInputComponent.BindAction(FManipulationInputs::kSelectEntity, IE_Pressed, this, &UManipulationInputComponent::OnSelectEntityPressed);
    InInputComponent.BindAction(FManipulationInputs::kSelectEntity, IE_Released, this, &UManipulationInputComponent::OnSelectEntityReleased);
    InInputComponent.BindAction(FManipulationInputs::kSelectAdditionalEntity, IE_Pressed, this, &UManipulationInputComponent::OnSelectAdditionalEntityPressed);
    InInputComponent.BindAction(FManipulationInputs::kSelectAdditionalEntity, IE_Released, this, &UManipulationInputComponent::OnSelectAdditionalEntityReleased);
}

void UManipulationInputComponent::Bind(APawn& InPawn)
{
    Pawn = &InPawn;

    GetWidget().Bind(InPawn);
}

void UManipulationInputComponent::OnSelectEntityPressed()
{
    if (bSelectEntityEnabled)
    {
        bSelectEntityEnabled = false;

        SelectedEntities.Reset();

        GetWidget().ClearSelection();

        SelectAdditionalEntity();
    }
}

void UManipulationInputComponent::OnSelectEntityReleased()
{
    bSelectEntityEnabled = true;
}

void UManipulationInputComponent::OnSelectAdditionalEntityPressed()
{
    if (bSelectAdditionalEntityEnabled)
    {
        bSelectAdditionalEntityEnabled = false;

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