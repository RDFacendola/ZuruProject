
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "ZuruWidget.h"

#include "ManipulationWidget.generated.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION WIDGET                                                  */
/************************************************************************/

// Represents a view associated to a manipulation input component.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = ViewComponents)
class ZURURDF_API UManipulationWidget : public UZuruWidget
{
    GENERATED_BODY()

public:

    // Stencil value which disables custom stencil write.
    static const int32 kDisableCustomStencil = -1;

    // Stencil value for selected entities.
    static const int32 kSelectedEntityCustomDepth = 1;
    
    // Bind to the player controller.
    void Bind(APlayerController& InPlayerController);

    // Bind to a pawn.
    void Bind(APawn& InPawn);

    // Add a new entity to the selection.
    void SelectEntity(AZuruEntity& InEntity);

    // Remove an entity from the selection.
    void DeselectEntity(AZuruEntity& InEntity);

    // Remove all selected entities.
    void ClearSelection();

    // Event notified whenever the spawn table button is clicked.
    FOnButtonClickedEvent& OnSpawnTableClicked();

    // Event notified whenever the spawn chair button is clicked.
    FOnButtonClickedEvent& OnSpawnChairClicked();

protected:

    // Button used to spawn tables.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* SpawnTableWidget{ nullptr };

    // Button used o spawn chairs.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* SpawnChairWidget { nullptr };

private:

    // Set the custom stencil value written by primitives in the provided entity.
    // Negative value disable the custom stencil write.
    void SetEntityStencilValue(AZuruEntity& InEntity, int32 InValue);

    // Selected entity set.
    UPROPERTY()
    TSet<AZuruEntity*> SelectedEntities;

    // A post process material applied to the player camera to show the current view status with 3D visual clues.
    UPROPERTY(EditAnywhere, Category = View)
    UMaterialInterface* PostProcessMaterial{ nullptr };

};

// ==================================================================== //
