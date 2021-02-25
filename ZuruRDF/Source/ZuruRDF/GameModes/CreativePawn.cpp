
// ==================================================================== //

#include "CreativePawn.h"

// ==================================================================== //

ACreativePawn::ACreativePawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACreativePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreativePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACreativePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// ==================================================================== //

