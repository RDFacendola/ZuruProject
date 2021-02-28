
// ==================================================================== //

#include "CreativePlayerController.h"

#include "CreativePawn.h"

// ==================================================================== //

ACreativePlayerController::ACreativePlayerController()
{
	CameraInputComponent = CreateDefaultSubobject<UFreeCameraInputComponent>(TEXT("CameraInput"));
}

void ACreativePlayerController::Tick(float InDeltaSeconds)
{
	Super::Tick(InDeltaSeconds);

	CameraInputComponent->Advance(InDeltaSeconds);
}

void ACreativePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ensure(InputComponent);

	CameraInputComponent->Bind(*InputComponent);
}

void ACreativePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ensure(InPawn);

	CameraInputComponent->Bind(*InPawn);
}

// ==================================================================== //

