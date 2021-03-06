
// ==================================================================== //

#include "FreeCameraInputComponent.h"

#include "ZuruRDF/GameModes/Inputs/CameraInputs.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

/************************************************************************/
/* FREE CAMERA INPUT COMPONENT                                          */
/************************************************************************/

void UFreeCameraInputComponent::Bind(AGameModeBase& InGameMode)
{
    // Camera has no business with the game mode.
}

void UFreeCameraInputComponent::Bind(APlayerController& InPlayerController)
{
    InPlayerController.bShowMouseCursor = true;

    GetWidget().Bind(InPlayerController);

    // Widget->OnRotateClockwiseClicked().AddDynamic(this, &UFreeCameraInputComponent::OnTopViewClicked);
}

void UFreeCameraInputComponent::Bind(UInputComponent& InInputComponent)
{
    InInputComponent.BindAxis(FCameraInputs::kCameraForward, this, &UFreeCameraInputComponent::OnForwardAxis);
    InInputComponent.BindAxis(FCameraInputs::kCameraRight, this, &UFreeCameraInputComponent::OnRightAxis);
    InInputComponent.BindAxis(FCameraInputs::kCameraOrbit, this, &UFreeCameraInputComponent::OnOrbitAxis);
    InInputComponent.BindAxis(FCameraInputs::kCameraPivot, this, &UFreeCameraInputComponent::OnPivotAxis);
    InInputComponent.BindAxis(FCameraInputs::kCameraDistance, this, &UFreeCameraInputComponent::OnDistanceAxis);
    InInputComponent.BindAxis(FCameraInputs::kCameraDragForward, this, &UFreeCameraInputComponent::OnForwardDragAxis);
    InInputComponent.BindAxis(FCameraInputs::kCameraDragRight, this, &UFreeCameraInputComponent::OnRightDragAxis);

    InInputComponent.BindAction(FCameraInputs::kCameraTopView, IE_Pressed, this, &UFreeCameraInputComponent::OnTopViewPressed);
    InInputComponent.BindAction(FCameraInputs::kCameraTopView, IE_Released, this, &UFreeCameraInputComponent::OnTopViewReleased);
    InInputComponent.BindAction(FCameraInputs::kCameraFrontView, IE_Pressed, this, &UFreeCameraInputComponent::OnFrontViewPressed);
    InInputComponent.BindAction(FCameraInputs::kCameraFrontView, IE_Released, this, &UFreeCameraInputComponent::OnFrontViewReleased);
    InInputComponent.BindAction(FCameraInputs::kCameraClockwise, IE_Pressed, this, &UFreeCameraInputComponent::OnClockwisePressed);
    InInputComponent.BindAction(FCameraInputs::kCameraClockwise, IE_Released, this, &UFreeCameraInputComponent::OnClockwiseReleased);
    InInputComponent.BindAction(FCameraInputs::kCameraCounterClockwise, IE_Pressed, this, &UFreeCameraInputComponent::OnCounterClockwisePressed);
    InInputComponent.BindAction(FCameraInputs::kCameraCounterClockwise, IE_Released, this, &UFreeCameraInputComponent::OnCounterClockwiseReleased);
    InInputComponent.BindAction(FCameraInputs::kCameraDragEnabled, IE_Pressed, this, &UFreeCameraInputComponent::OnDragCameraPressed);
    InInputComponent.BindAction(FCameraInputs::kCameraDragEnabled, IE_Released, this, &UFreeCameraInputComponent::OnDragCameraReleased);
}

void UFreeCameraInputComponent::Bind(APawn& InPawn)
{
    FreeCameraComponent = InPawn.FindComponentByClass<UFreeCameraComponent>();

    GetWidget().Bind(InPawn);
}

void UFreeCameraInputComponent::Advance(float InDeltaSeconds)
{
    // Disable orbit actions until clockwise and counterclockwise keys are released.

    if (!bClockwiseEnabled || !bCounterClockwiseEnabled)
    {
        Actions.Orbit = 0.0f;
    }

    if (FreeCameraComponent)
    {
        FreeCameraComponent->SetActions(Actions);
    }

    Actions = {};
}

void UFreeCameraInputComponent::OnForwardAxis(float InValue)
{
    if (!bDragEnabled)
    {
        Actions.Strafe.X += InValue;
    }
}

void UFreeCameraInputComponent::OnRightAxis(float InValue)
{
    if (!bDragEnabled)
    {
        Actions.Strafe.Y += InValue;
    }
}

void UFreeCameraInputComponent::OnOrbitAxis(float InValue)
{
    Actions.Orbit += InValue;
}

void UFreeCameraInputComponent::OnPivotAxis(float InValue)
{
    Actions.Pivot += InValue;
}

void UFreeCameraInputComponent::OnDistanceAxis(float InValue)
{
    Actions.Distance += InValue;
}

void UFreeCameraInputComponent::OnForwardDragAxis(float InValue)
{
    if (bDragEnabled)
    {
        Actions.Strafe.X += InValue;
    }
}

void UFreeCameraInputComponent::OnRightDragAxis(float InValue)
{
    if (bDragEnabled)
    {
        Actions.Strafe.Y += InValue;
    }
}

void UFreeCameraInputComponent::OnTopViewPressed()
{
    Actions.bTopView = bTopViewEnabled;
    bTopViewEnabled = false;
}

void UFreeCameraInputComponent::OnTopViewReleased()
{
    bTopViewEnabled = true;
}

void UFreeCameraInputComponent::OnTopViewClicked()
{
    OnTopViewPressed();
    OnTopViewReleased();
}

void UFreeCameraInputComponent::OnFrontViewPressed()
{
    Actions.bFrontView = bFrontViewEnabled;
    bFrontViewEnabled = false;
}

void UFreeCameraInputComponent::OnFrontViewReleased()
{
    bFrontViewEnabled = true;
}

void UFreeCameraInputComponent::OnFrontViewClicked()
{
    OnFrontViewPressed();
    OnFrontViewReleased();
}

void UFreeCameraInputComponent::OnClockwisePressed()
{
    Actions.bClockwise = bClockwiseEnabled;
    bClockwiseEnabled = false;
}

void UFreeCameraInputComponent::OnClockwiseReleased()
{
    bClockwiseEnabled = true;
}

void UFreeCameraInputComponent::OnClockwiseClicked()
{
    OnClockwisePressed();
    OnClockwiseReleased();
}

void UFreeCameraInputComponent::OnCounterClockwisePressed()
{
    Actions.bCounterClockwise = bCounterClockwiseEnabled;
    bCounterClockwiseEnabled = false;
}

void UFreeCameraInputComponent::OnCounterClockwiseReleased()
{
    bCounterClockwiseEnabled = true;
}

void UFreeCameraInputComponent::OnCounterClockwiseClicked()
{
    OnCounterClockwisePressed();
    OnCounterClockwiseReleased();
}

void UFreeCameraInputComponent::OnDragCameraPressed()
{
    bDragEnabled = true;
}

void UFreeCameraInputComponent::OnDragCameraReleased()
{
    bDragEnabled = false;
}

void UFreeCameraInputComponent::OnWidgetConstructed()
{
    // Bind to widget inputs.

    Widget->OnTopViewClicked().AddDynamic(this, &UFreeCameraInputComponent::OnTopViewClicked);
    Widget->OnFrontViewClicked().AddDynamic(this, &UFreeCameraInputComponent::OnFrontViewClicked);
    Widget->OnClockwiseClicked().AddDynamic(this, &UFreeCameraInputComponent::OnClockwiseClicked);
    Widget->OnCounterClockwiseClicked().AddDynamic(this, &UFreeCameraInputComponent::OnCounterClockwiseClicked);
}

UFreeCameraWidget& UFreeCameraInputComponent::GetWidget()
{
    if (!Widget)
    {
        auto WidgetConcreteClass = WidgetClass ? WidgetClass : UFreeCameraWidget::StaticClass();

        Widget = CreateWidget<UFreeCameraWidget>(GetWorld(), WidgetConcreteClass);

        Widget->OnConstructed.AddDynamic(this, &UFreeCameraInputComponent::OnWidgetConstructed);
    }

    return *Widget;
}

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //
