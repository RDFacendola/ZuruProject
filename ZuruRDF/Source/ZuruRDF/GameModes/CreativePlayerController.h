
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Math/Vector.h"
#include "CreativePawn.h"

#include "Components/FreeCameraInputComponent.h"
#include "Components/ManipulationInputComponent.h"

#include "CreativePlayerController.generated.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE PLAYER CONTROLLER                                           */
/************************************************************************/

// Models a player's will in "creative" game mode.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API ACreativePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ACreativePlayerController();

	void Tick(float InDeltaSeconds) override;

	bool ProcessConsoleExec(const TCHAR* InCommand, FOutputDevice& InOutputDevice, UObject* InExecutor) override;

protected:
	
	void BeginPlay() override;

	void SetupInputComponent() override;

	void OnPossess(APawn* InPawn) override;

private:

	// Handles camera-related inputs.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UFreeCameraInputComponent* CameraInputComponent{ nullptr };

	// Handles manipulation-related inputs.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UManipulationInputComponent* ManipulationInputComponent{ nullptr };

};

// ==================================================================== //
