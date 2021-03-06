
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "FreeCameraWidget.generated.h"

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA WIDGET                                                   */
/************************************************************************/

// Represents a view associated to a free-camera input component.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = ViewComponents)
class ZURURDF_API UFreeCameraWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    // Bind to the player controller.
    void Bind(APlayerController& InPlayerController);

    // Bind to a pawn.
    void Bind(APawn& InPawn);

private:


};

// ==================================================================== //
