
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "ZuruRDF/GameModes/Inputs/ZuruInputs.h"
#include "ZuruRDF/Core/ZuruEntity.h"
#include "ZuruRDF/Core/ZuruGizmoComponent.h"

#include "ManipulationGizmo.generated.h"

// ==================================================================== //

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManipulationGizmoAxis, float, Value);

/************************************************************************/
/* MANIPULATION GIZMO ACTIONS                                           */
/************************************************************************/

// Set of manipulation gizmo actions.
//
// @author Raffaele D. Facendola - March 2021.
struct FManipulationGizmoActions
{
    // Active gizmo.
    UZuruGizmoComponent* ActiveGizmo;

    // Gizmo position.
    TOptional<FVector2D> AbsolutePosition{ FVector2D::ZeroVector };

    // Gizmo rotation.
    TOptional<FRotator> AbsoluteRotation{ FRotator::ZeroRotator };
};

/************************************************************************/
/* MANIPULATION GIZMO                                                   */
/************************************************************************/

// Actor used to display 3D gizmo control over an entity being manipulated.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = Entities)
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

    // Refresh the gizmo status.
    void Advance(float InDeltaSeconds);

    // Declare the selected entity set.
    void SelectEntities(const TSet<AZuruEntity*>& InSelectedEntities);

    // Check whether a gizmo is being interacted with and activate it if necessary.
    bool ConditionalActivateGizmo();

    // Deactivate the active gizmo (if any).
    void DeactivateGizmo();

    // Access the gizmo actions.
    const FManipulationGizmoActions& GetActions() const;

    // Consume the gizmo actions.
    void ConsumeActions();

    void PostInitProperties() override;

private:

    // Called whenever the gizmo drag is detected.
    void OnDragAxis(float InValue);

    // Retrieve the list of gizmos in the provided.
    void RetrieveGizmos(const TSet<AZuruEntity*>& InSelectedEntities);

    // Generate a new gizmo component (or recycle an unused one).
    UZuruGizmoComponent& SpawnProceduralGizmoComponent();

    // Invalidate all procedurally-generated gizmos on this actor.
    void InvalidateGizmos();

    // Gizmo root component.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    USceneComponent* GizmoRoot{ nullptr };

    // Gizmo used to translate the entity..
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UZuruGizmoComponent* TranslateGizmoComponent{ nullptr };

    // Gizmo used to rotate the entity.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UZuruGizmoComponent* RotateGizmoComponent { nullptr };

    // List of entity procedurally-generated gizmos.
    UPROPERTY()
    TArray<UZuruGizmoComponent*> ProceduralGizmoComponents;

    // Pooled gizmo components ready to be used.
    UPROPERTY()
    TArray<UZuruGizmoComponent*> ProceduralGizmoComponentPool;

    // Concrete class of procedurally-generated gizmos.
    UPROPERTY(EditAnywhere, Category = Gizmo)
    TSubclassOf<UZuruGizmoComponent> ProceduralGizmoComponentClass{ UZuruGizmoComponent::StaticClass() };

    // Object type used to filter out gizmos.
    UPROPERTY(EditAnywhere, Category = Gizmo)
    TEnumAsByte<EObjectTypeQuery> GizmoObjectType{ EObjectTypeQuery::ObjectTypeQuery3 };

    // Object type used to filter out floors.
    UPROPERTY(EditAnywhere, Category = Gizmo)
    TEnumAsByte<EObjectTypeQuery> FloorObjectType{ EObjectTypeQuery::ObjectTypeQuery2 };

    // Player controller this gizmo belongs to.
    UPROPERTY()
    APlayerController* PlayerController{ nullptr };

    // Pending gizmo actions.
    FManipulationGizmoActions GizmoActions;

    // Whether the drag action has been consumed.
    bool bDragAxisConsume{ true };

    // List of entities selected so far.
    TSet<AZuruEntity*> SelectedEntities;
};

// ==================================================================== //

