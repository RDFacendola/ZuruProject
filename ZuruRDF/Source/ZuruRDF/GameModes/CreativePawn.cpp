
// ==================================================================== //

#include "CreativePawn.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

// ==================================================================== //

ACreativePawn::ACreativePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	// Root component.

	PawnComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pawn"));
	PawnComponent->SetGenerateOverlapEvents(false);
	PawnComponent->SetHiddenInGame(true);

	SetRootComponent(PawnComponent);

	// Pivot component.

	PivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	
	PivotComponent->SetupAttachment(PawnComponent);

	// Camera component.

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	CameraComponent->SetupAttachment(PivotComponent);

}

void ACreativePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACreativePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Just move the camera along the forward vector: pivot will take care of the inclination of the camera automatically.

	CameraComponent->SetRelativeLocation(FVector{ -CameraDistance, 0.0f, CameraVerticalOffset });

}

void ACreativePawn::Strafe(const FVector& InStrafe)
{
	SetActorRelativeLocation(InStrafe);
}

void ACreativePawn::Orbit(float InOrbit)
{
	SetActorRelativeRotation(FRotator(0.0f, 0.0f, InOrbit));
}

void ACreativePawn::Pivot(float InPivot)
{
	PivotComponent->SetRelativeRotation(FRotator(0.0f, InPivot, 0.0f));
}

// ==================================================================== //

