
// ==================================================================== //

#include "CreativePlayerController.h"

#include "CreativePawn.h"

// ==================================================================== //

ACreativePlayerController::ACreativePlayerController()
{
	CameraInputComponent = CreateDefaultSubobject<UFreeCameraInputComponent>(TEXT("CameraInput"));
	ManipulationInputComponent = CreateDefaultSubobject<UManipulationInputComponent>(TEXT("ManipulationInput"));
}

void ACreativePlayerController::Tick(float InDeltaSeconds)
{
	Super::Tick(InDeltaSeconds);

	CameraInputComponent->Advance(InDeltaSeconds);
}

bool ACreativePlayerController::ProcessConsoleExec(const TCHAR* InCommand, FOutputDevice& InOutputDevice, UObject* InExecutor)
{
	auto Handled = Super::ProcessConsoleExec(InCommand, InOutputDevice, InExecutor);
	
	Handled |= CameraInputComponent->ProcessConsoleExec(InCommand, InOutputDevice, InExecutor);
	Handled |= ManipulationInputComponent->ProcessConsoleExec(InCommand, InOutputDevice, InExecutor);
	
	return Handled;
}

void ACreativePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ensure(InputComponent);

	CameraInputComponent->Bind(*InputComponent);
	ManipulationInputComponent->Bind(*InputComponent);
}

void ACreativePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ensure(InPawn);

	CameraInputComponent->Bind(*InPawn);
	ManipulationInputComponent->Bind(*InPawn);
}

// ==================================================================== //

