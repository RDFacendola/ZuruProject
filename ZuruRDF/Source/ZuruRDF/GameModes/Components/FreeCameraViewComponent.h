
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FreeCameraComponent.h"

#include "FreeCameraViewComponent.generated.h"

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA VIEW COMPONENT                                           */
/************************************************************************/

// Represents a view associated to a free-camera input component.
//
// @author Raffaele D. Facendola - March 2021.
UCLASS(Blueprintable, BlueprintType, ClassGroup = ViewComponents)
class ZURURDF_API UFreeCameraViewComponent : public UActorComponent
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
