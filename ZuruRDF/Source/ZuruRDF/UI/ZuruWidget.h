
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "ZuruWidget.generated.h"

// ==================================================================== //

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWidgetConstructed);

/************************************************************************/
/* ZURU WIDGET                                                          */
/************************************************************************/

// Base class for all widgets.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = ViewComponents)
class ZURURDF_API UZuruWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    // Bind to the player controller.
    virtual void Bind(APlayerController& InPlayerController);

    // Bind to a pawn.
    virtual void Bind(APawn& InPawn);

    // Called when the widget is constructed.
    FOnWidgetConstructed OnConstructed;

protected:

    virtual void OnWidgetRebuilt() override;

};

// ==================================================================== //
