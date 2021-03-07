
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/Slider.h"

#include "ZuruWidget.h"

#include "FreeCameraWidget.generated.h"

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA WIDGET                                                   */
/************************************************************************/

// Represents a view associated to a free-camera input component.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = ViewComponents)
class ZURURDF_API UFreeCameraWidget : public UZuruWidget
{
    GENERATED_BODY()

public:

    void Bind(APlayerController& InPlayerController) override;

    void Bind(APawn& InPawn) override;

    // Set the camera orbit value in normalized range [0;1].
    void SetOrbitValue(float InOrbit);

    // Set the camera pivot value in normalized range [0;1].
    void SetPivotValue(float InPivot);

    // Set the camera distance value in normalized range [0;1].
    void SetDistanceValue(float InDistance);

    // Event notified whenever the clockwise button is clicked.
    FOnButtonClickedEvent& OnClockwiseClicked();

    // Event notified whenever the counter-clockwise button is detected.
    FOnButtonClickedEvent& OnCounterClockwiseClicked();

    // Event notified whenever the front-view button is clicked.
    FOnButtonClickedEvent& OnFrontViewClicked();

    // Event notified whenever the top-view button is notified.
    FOnButtonClickedEvent& OnTopViewClicked();

    // Event notified whenever the orbit slider value changes.
    FOnFloatValueChangedEvent& OnOrbitChanged();

    // Event notified whenever the pivot slider value changes.
    FOnFloatValueChangedEvent& OnPivotChanged();

    // Event notified whenever the distance slider value changes.
    FOnFloatValueChangedEvent& OnDistanceChanged();

protected:

    // Called whenever user input begins.
    UFUNCTION()
    void OnInputBegin();

    // Called whenever user input ends.
    UFUNCTION()
    void OnInputEnd();

    // Button associated to the clockwise action. 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* ClockwiseWidget{ nullptr };

    // Button associated to the counter-clockwise action.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* CounterClockwiseWidget { nullptr };

    // Button associated to the front view action.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* FrontViewWidget { nullptr };

    // Button associated to the top view action.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* TopViewWidget { nullptr };

    // Slider associated to the orbit input.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    USlider* OrbitWidget{ nullptr };

    // Slider associated to the pivot input.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    USlider* PivotWidget{ nullptr };

    // Slider associated to the distance input.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    USlider* DistanceWidget{ nullptr };

    // Whether the user is currently interacting with the widget.
    bool bUserInteraction{ false };


};

// ==================================================================== //
