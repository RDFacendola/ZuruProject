
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"

#include "Components/FreeCameraComponent.h"

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

	virtual void Tick(float InDeltaTime) override;

protected:
	
	virtual void BeginPlay() override;

private:

	// A dummy mesh to locate the pawn. Hidden in game.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PawnComponent{ nullptr };

	// Pivot component used to raise or lower the camera relative to its target.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* PivotComponent{ nullptr };

	// Main camera.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UFreeCameraComponent* FreeCameraComponent{ nullptr };

};

// ==================================================================== //
