
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "ZuruRDF/GameModes/Inputs/ZuruInputs.h"
#include "ZuruRDF/Core/ZuruEntity.h"
#include "ZuruRDF/Core/ZuruGizmoComponent.h"
#include "ZuruRDF/Core/ZuruTranslationGizmoComponent.h"
#include "ZuruRDF/Core/ZuruRotationGizmoComponent.h"

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

    // Gizmo translation.
    FVector2D Translation{ FVector2D::ZeroVector };

    // Gizmo rotation.
    FRotator Rotation{ FRotator::ZeroRotator };
};

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

    // Called whenever the gizmo forward/backward drag input is detected.
    void OnForwardDragAxis(float InValue);

    // Called whenever the gizmo right/left drag input is detected.
    void OnRightDragAxis(float InValue);

    // Gizmo root component.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    USceneComponent* GizmoRoot{ nullptr };

    // Gizmo used to translate the entity..
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UZuruTranslationGizmoComponent* TranslateGizmoComponent{ nullptr };

    // Gizmo used to rotate the entity.
    UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    UZuruRotationGizmoComponent* RotateGizmoComponent { nullptr };

    // Object type used to filter out gizmos.
    UPROPERTY(EditAnywhere, Category = Input)
    TEnumAsByte<EObjectTypeQuery> GizmoObjectType{ EObjectTypeQuery::ObjectTypeQuery3 };

    // Player controller this gizmo belongs to.
    UPROPERTY()
    APlayerController* PlayerController{ nullptr };

    // Pending gizmo actions.
    FManipulationGizmoActions GizmoActions;
};

// ==================================================================== //

