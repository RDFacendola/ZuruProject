
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "CreativePawn.generated.h"

// ==================================================================== //

/************************************************************************/
/* CREATIVE PAWN                                                        */
/************************************************************************/

// An invisible pawn used mainly as a camera target during "creative" game mode.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API ACreativePawn : public APawn
{
	GENERATED_BODY()

public:

	ACreativePawn();

protected:
	
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

// ==================================================================== //
