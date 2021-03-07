
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

    if (OrbitWidget)
    {
        OrbitWidget->OnMouseCaptureBegin.AddDynamic(this, &UFreeCameraWidget::OnInputBegin);
        OrbitWidget->OnMouseCaptureEnd.AddDynamic(this, &UFreeCameraWidget::OnInputEnd);
    }

    if (PivotWidget)
    {
        PivotWidget->OnMouseCaptureBegin.AddDynamic(this, &UFreeCameraWidget::OnInputBegin);
        PivotWidget->OnMouseCaptureEnd.AddDynamic(this, &UFreeCameraWidget::OnInputEnd);
    }

    if (DistanceWidget)
    {
        DistanceWidget->OnMouseCaptureBegin.AddDynamic(this, &UFreeCameraWidget::OnInputBegin);
        DistanceWidget->OnMouseCaptureEnd.AddDynamic(this, &UFreeCameraWidget::OnInputEnd);
    }
}

void UFreeCameraWidget::SetOrbitValue(float InOrbit)
{
    if (OrbitWidget && !bUserInteraction)
    {
        OrbitWidget->SetValue(InOrbit);
    }
}

void UFreeCameraWidget::SetPivotValue(float InPivotValue)
{
    if (PivotWidget && !bUserInteraction)
    {
        PivotWidget->SetValue(InPivotValue);
    }
}

void UFreeCameraWidget::SetDistanceValue(float InDistance)
{
    if (DistanceWidget && !bUserInteraction)
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

void UFreeCameraWidget::OnInputBegin()
{
    bUserInteraction = true;
}

void UFreeCameraWidget::OnInputEnd()
{
    bUserInteraction = false;
}

// ==================================================================== //
