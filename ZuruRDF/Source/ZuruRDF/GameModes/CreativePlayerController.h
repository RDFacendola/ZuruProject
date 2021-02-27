
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Math/Vector.h"
#include "FreeCameraComponent.h"

#include "CreativePlayerController.generated.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE PLAYER CONTROLLER                                           */
/************************************************************************/

// A player controller for the "creative" game mode.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API ACreativePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ACreativePlayerController();

	void Tick(float DeltaSeconds) override;

protected:
	
	void SetupInputComponent() override;

	void OnPossess(APawn* InPawn) override;

private:

	// The camera component.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UFreeCameraComponent* CameraComponent{ nullptr };
	
};

// ==================================================================== //
