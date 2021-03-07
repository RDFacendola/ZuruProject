
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/GameModeBase.h"

#include "ManipulationComponent.h"

#include "ZuruRDF/UI/ManipulationWidget.h"
#include "ManipulationGizmo.h"

#include "ManipulationInputComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION INPUT COMPONENT                                         */
/************************************************************************/

// A component used to read manipulation-related inputs on a player controller.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API UManipulationInputComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    // Bind to the game mode. Server-side only.
    void Bind(AGameModeBase& InGameMode);

    // Bind to the player controller.
    void Bind(APlayerController& InPlayerController);

    // Bind to an input component.
    void Bind(UInputComponent& InInputComponent);

    // Bind to a pawn.
    void Bind(APawn& InPawn);

private:

    // Called whenever the select entity input is pressed.
    void OnSelectEntityPressed();

    // Called whenever the select entity input is released.
    void OnSelectEntityReleased();

    // Called whenever the select additional entity input is pressed.
    void OnSelectAdditionalEntityPressed();

    // Called whenever the select additional entity input is released.
    void OnSelectAdditionalEntityReleased();

    // Called whenever the spawn table input is clicked.
    UFUNCTION()
    void OnSpawnTableClicked();

    // Called whenever the spawn chair input is clicked.
    UFUNCTION()
    void OnSpawnChairClicked();

    // Add the entity under mouse cursor to the selection, if possible.
    void SelectAdditionalEntity();

    // Called whenever the widget is constructed.
    UFUNCTION()
    void OnWidgetConstructed();

    // Get the widget associated to this component.
    UManipulationWidget& GetWidget();

    // Spawn an entity by key.
    UFUNCTION(Exec)
    void SpawnEntity(const FName& InEntityKey);

    // Spawn an entity by key at given coordinates.
    void SpawnEntityAt(const FName& InEntityKey, const FTransform& InEntityTransform);

    // Object type used to filter out selected entities.
    UPROPERTY(EditAnywhere, Category = Input)
    TEnumAsByte<EObjectTypeQuery> EntityObjectType{ EObjectTypeQuery::ObjectTypeQuery1 };

    // Widget class.
    UPROPERTY(EditAnywhere, Category = View)
    TSubclassOf<UManipulationWidget> WidgetClass{ UManipulationWidget::StaticClass() };

    // Gizmo class.
    UPROPERTY(EditAnywhere, Category = View)
    TSubclassOf<AManipulationGizmo> GizmoClass{ AManipulationGizmo::StaticClass() };

    // Controlled pawn.
    UPROPERTY()
    APawn* Pawn{ nullptr };

    // The entity-manipulation component counterpart on the game mode.
    UPROPERTY()
    UManipulationComponent* ManipulationComponent{ nullptr };

    // Owning player controller.
    UPROPERTY()
    APlayerController* PlayerController{ nullptr };

    // Widget instance.
    UPROPERTY()
    UManipulationWidget* Widget{ nullptr };

    // List of selected entities.
    UPROPERTY()
    TSet<AZuruEntity*> SelectedEntities;

    // Enable the select-entity action. Avoids repeating the action while the key's pressed.
    bool bSelectEntityEnabled{ true };

    // Enable the select-additional-entity action. Avoids repeating the action while the key's pressed.
    bool bSelectAdditionalEntityEnabled{ true };

};

// ==================================================================== //
