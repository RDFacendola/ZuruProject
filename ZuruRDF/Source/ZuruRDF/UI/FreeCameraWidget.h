
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"

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

    // Event notified whenever the clockwise button is clicked.
    FOnButtonClickedEvent& OnClockwiseClicked();

    // Event notified whenever the counter-clockwise button is detected.
    FOnButtonClickedEvent& OnCounterClockwiseClicked();

    // Event notified whenever the front-view button is clicked.
    FOnButtonClickedEvent& OnFrontViewClicked();

    // Event notified whenever the top-view button is notified.
    FOnButtonClickedEvent& OnTopViewClicked();

protected:

    // Button 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* ClockwiseWidget{ nullptr };

    // Button 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* CounterClockwiseWidget { nullptr };

    // Button 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* FrontViewWidget { nullptr };

    // Button 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widgets)
    UButton* TopViewWidget { nullptr };

};

// ==================================================================== //
