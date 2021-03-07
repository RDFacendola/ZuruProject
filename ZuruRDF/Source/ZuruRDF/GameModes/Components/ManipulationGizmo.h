
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "ZuruRDF/Core/ZuruGizmo.h"
#include "ZuruRDF/Core/ZuruEntity.h"

#include "ManipulationGizmo.generated.h"

// ==================================================================== //

/************************************************************************/
/* MANIPULATION GIZMO                                                   */
/************************************************************************/

// Actor used to display 3D gizmo control over an entity being manipulated.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Entites)
class ZURURDF_API AManipulationGizmo : public AActor
{
    GENERATED_BODY()
    
public:

    // Create a new entity.
    AManipulationGizmo();

    // Bind to the player controller.
    void Bind(APlayerController& InPlayerController);

    // Bind to an input component.
    void Bind(UInputComponent& InInputComponent);

    // Add a new entity to the selection.
    void SelectEntity(AZuruEntity& InEntity);

    // Remove an entity from the selection.
    void DeselectEntity(AZuruEntity& InEntity);

    // Remove all selected entities.
    void ClearSelection();

    void PostInitProperties() override;

protected:

private:

    // Move the gizmo under the selected entities (or hide it if no entity is selected).
    void MoveGizmo();

    // Called whenever the gizmo enable drag input is pressed.
    void OnDragGizmoPressed();

    // Called whenever the gizmo enable drag input is released.
    void OnDragGizmoReleased();

    // Called whenever the gizmo forward/backward drag input is detected.
    void OnForwardDragAxis(float InValue);

    // Called whenever the gizmo right/left drag input is detected.
    void OnRightDragAxis(float InValue);

    // Gizmo root component.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    USceneComponent* GizmoRoot{ nullptr };

    // Gizmo used to translate the entity..
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* TranslateGizmoComponent{ nullptr };

    // Gizmo used to rotate the entity.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* RotateGizmoComponent { nullptr };

    // Object type used to filter out gizmos.
    UPROPERTY(EditAnywhere, Category = Input)
    TEnumAsByte<EObjectTypeQuery> GizmoObjectType{ EObjectTypeQuery::ObjectTypeQuery3 };

    // Player controller this gizmo belongs to.
    UPROPERTY()
    APlayerController* PlayerController{ nullptr };

    // Selected entity set.
    UPROPERTY()
    TSet<AZuruEntity*> SelectedEntities;

    // Enable the gizmo drag input.
    bool bDragEnabled{ false };

};

// ==================================================================== //

