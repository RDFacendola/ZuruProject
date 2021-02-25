
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"

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

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	virtual void BeginPlay() override;

private:

	// A dummy mesh to locate the pawn. Hidden in game.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Root{ nullptr };

	// Pivot component used to raise or lower the camera relative to its target.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Pivot{ nullptr };

	// Main camera.
	UPROPERTY(Category = Components, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera{ nullptr };

	// Desired distance of the camera from the target, in world units.
	UPROPERTY(Category = Configuration, EditAnywhere)
	float CameraDistance{ 200.0f };

	// Desired vertical offset of the camera relative to its target, in world units.
	UPROPERTY(Category = Configuration, EditAnywhere)
	float CameraVerticalOffset{ 50.0f };

	// Desired camera angle, relative to its target, in degrees.
	UPROPERTY(Category = Configuration, EditAnywhere)
	float CameraInclination{ 45.0f };
};

// ==================================================================== //
