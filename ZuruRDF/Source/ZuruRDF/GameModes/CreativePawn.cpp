
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

	CameraComponent = CreateDefaultSubobject<UFreeCameraComponent>(TEXT("Camera"));

	CameraComponent->SetupAttachment(PivotComponent);

}

void ACreativePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACreativePawn::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	CameraComponent->Advance(InDeltaTime);

}

// ==================================================================== //

