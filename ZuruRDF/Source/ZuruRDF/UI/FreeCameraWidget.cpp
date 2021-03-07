
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

void UFreeCameraWidget::SetOrbitValue(float InOrbit)
{
    if (OrbitWidget)
    {
        OrbitWidget->SetValue(InOrbit);
    }
}

void UFreeCameraWidget::SetPivotValue(float InPivotValue)
{
    if (PivotWidget)
    {
        PivotWidget->SetValue(InPivotValue);
    }
}

void UFreeCameraWidget::SetDistanceValue(float InDistance)
{
    if (DistanceWidget)
    {
        DistanceWidget->SetValue(InDistance);
    }
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

FOnFloatValueChangedEvent& UFreeCameraWidget::OnOrbitChanged()
{
    return OrbitWidget->OnValueChanged;
}

FOnFloatValueChangedEvent& UFreeCameraWidget::OnPivotChanged()
{
    return PivotWidget->OnValueChanged;
}

FOnFloatValueChangedEvent& UFreeCameraWidget::OnDistanceChanged()
{
    return DistanceWidget->OnValueChanged;
}

// ==================================================================== //
