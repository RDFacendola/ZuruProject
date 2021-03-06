
// ==================================================================== //

#include "FreeCameraWidget.h"

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA WIDGET                                                   */
/************************************************************************/

void UFreeCameraWidget::Bind(APlayerController& InPlayerController)
{

}

void UFreeCameraWidget::Bind(APawn& InPawn)
{
    AddToViewport();
}

FOnButtonClickedEvent& UFreeCameraWidget::OnClockwiseClicked()
{
    return ClockwiseWidget->OnClicked;
}

FOnButtonClickedEvent& UFreeCameraWidget::OnCounterClockwiseClicked()
{
    return CounterClockwiseWidget->OnClicked;
}

FOnButtonClickedEvent& UFreeCameraWidget::OnFrontViewClicked()
{
    return FrontViewWidget->OnClicked;
}

FOnButtonClickedEvent& UFreeCameraWidget::OnTopViewClicked()
{
    return TopViewWidget->OnClicked;
}

// ==================================================================== //
