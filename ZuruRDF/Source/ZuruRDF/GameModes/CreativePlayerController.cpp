
// ==================================================================== //

#include "CreativePlayerController.h"

#include "CreativeInputs.h"
#include "CreativePawn.h"

// ==================================================================== //

ACreativePlayerController::ACreativePlayerController()
{
	CameraComponent = CreateDefaultSubobject<UFreeCameraComponent>(TEXT("Camera"));
}

void ACreativePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

void ACreativePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	ensure(InputComponent);

	CameraComponent->Bind(*InputComponent);
}

void ACreativePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);



}

// ==================================================================== //

