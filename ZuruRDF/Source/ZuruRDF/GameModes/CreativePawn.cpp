
// ==================================================================== //

#include "CreativePawn.h"
#include "Math/Vector.h"

// ==================================================================== //

ACreativePawn::ACreativePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root component.

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pawn"));
	Root->SetGenerateOverlapEvents(false);
	Root->SetHiddenInGame(true);

	SetRootComponent(Root);

	// Pivot component.

	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	
	Pivot->SetupAttachment(Root);

	// Camera component.

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Camera->SetupAttachment(Pivot);

}

void ACreativePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACreativePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Just move the camera along the forward vector: pivot will take care of the inclination of the camera automatically.

	Camera->SetRelativeLocation(FVector{ -CameraDistance, 0.0f, CameraVerticalOffset });
	Pivot->SetRelativeRotation(FRotator{ -CameraInclination, 0.0f, 0.0f });
}

void ACreativePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// ==================================================================== //

