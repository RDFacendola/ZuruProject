
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

	FreeCameraComponent = CreateDefaultSubobject<UFreeCameraComponent>(TEXT("Camera"));

	FreeCameraComponent->SetupAttachment(PivotComponent);

}

void ACreativePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACreativePawn::Tick(float InDeltaTime)
{
	Super::Tick(InDeltaTime);

	FreeCameraComponent->Advance(InDeltaTime);
}

// ==================================================================== //

