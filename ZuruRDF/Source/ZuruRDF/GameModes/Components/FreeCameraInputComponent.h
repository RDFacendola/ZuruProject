
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FreeCameraComponent.h"

#include "FreeCameraInputComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA INPUT COMPONENT                                          */
/************************************************************************/

// A component used to read free-camera inputs on a player controller.
// This component is meant to aggregate raw inputs from the user and send relative actions to the pawn.
// This component automatically binds to a FreeCameraComponent counterpart upon pawn possession.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API UFreeCameraInputComponent : public UActorComponent
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

    // Advance the component status.
    void Advance(float InDeltaSeconds);

private:

    // Called whenever the camera forward/backward input is detected.
    void OnForwardAxis(float InValue);

    // Called whenever the camera right/left input is detected.
    void OnRightAxis(float InValue);

    // Called whenever the camera orbit input is detected.
    void OnOrbitAxis(float InValue);

    // Called whenever the camera pivot input is detected.
    void OnPivotAxis(float InValue);

    // Called whenever the camera distance input is detected.
    void OnDistanceAxis(float InValue);
    
    // Called whenever the camera forward/backward drag input is detected.
    void OnForwardDragAxis(float InValue);

    // Called whenever the camera right/left drag input is detected.
    void OnRightDragAxis(float InValue);

    // Called whenever the camera pivot snap top input is pressed.
    void OnTopViewPressed();

    // Called whenever the camera pivot snap top input is released.
    void OnTopViewReleased();

    // Called whenever the camera pivot snap front input is pressed.
    void OnFrontViewPressed();

    // Called whenever the camera pivot snap front input is released.
    void OnFrontViewReleased();

    // Called whenever the camera orbit snap right input is pressed.
    void OnClockwisePressed();

    // Called whenever the camera orbit snap right input is released.
    void OnClockwiseReleased();

    // Called whenever the camera orbit snap left input is pressed.
    void OnCounterClockwisePressed();

    // Called whenever the camera orbit snap left input is released.
    void OnCounterClockwiseReleased();

    // Called whenever the camera enable drag input is pressed.
    void OnDragCameraPressed();

    // Called whenever the camera enable drag input is released.
    void OnDragCameraReleased();

    // The free-camera component counterpart on the pawn.
    UPROPERTY()
    UFreeCameraComponent* FreeCameraComponent{ nullptr };

    // Current camera actions.
    FFreeCameraActions Actions;

    // Enable the actual pivot snap top action. Avoids repeating the action while the keys are pressed.
    bool bTopViewEnabled{ true };

    // Enable the actual pivot snap front action. Avoids repeating the action while the keys are pressed.
    bool bFrontViewEnabled{ true };

    // Enable the actual orbit snap right action. Avoids repeating the action while the keys are pressed.
    bool bClockwiseEnabled{ true };

    // Enable the actual orbit snap left action. Avoids repeating the action while the keys are pressed.
    bool bCounterClockwiseEnabled{ true };

    // Enable the camera drag input.
    bool bDragEnabled{ false };

};

// ==================================================================== //
