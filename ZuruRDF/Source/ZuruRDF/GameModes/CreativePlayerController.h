
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Math/Vector.h"
#include "Components/FreeCameraInputComponent.h"
#include "CreativePawn.h"

#include "CreativePlayerController.generated.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE PLAYER CONTROLLER                                           */
/************************************************************************/

// Models a player's will the "creative" game mode.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API ACreativePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ACreativePlayerController();

	void Tick(float InDeltaSeconds) override;

protected:
	
	void SetupInputComponent() override;

	void OnPossess(APawn* InPawn) override;

private:

	// Handles camera-specific inputs.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UFreeCameraInputComponent* CameraInputComponent{ nullptr };

};

// ==================================================================== //
