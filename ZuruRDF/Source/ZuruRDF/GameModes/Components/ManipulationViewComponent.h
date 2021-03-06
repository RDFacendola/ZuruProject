
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "ManipulationViewComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION VIEW COMPONENT                                          */
/************************************************************************/

// Represents a view associated to a manipulation input component.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = ViewComponents)
class ZURURDF_API UManipulationViewComponent : public UActorComponent
{
    GENERATED_BODY()

public:

    // Bind to the player controller.
    void Bind(APlayerController& InPlayerController);

    // Bind to a pawn.
    void Bind(APawn& InPawn);

    // Add a new entity to the selection.
    void SelectEntity(AZuruEntity& InEntity);

    // Remove all selected entities.
    void ClearSelection();

    void BeginPlay() override;

private:

    // Selected entity set.
    UPROPERTY()
    TArray<AZuruEntity*> SelectedEntities;

    // A post process material applied to the player camera to show the current view status with 3D visual clues.
    UPROPERTY(EditAnywhere, Category = View)
    UMaterialInterface* PostProcessMaterial{ nullptr };

};

// ==================================================================== //
