
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"

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

	// Move the pawn on the XY plane.
	void Strafe(const FVector& InStrafe);

	// Rotate the pawn on the Z axis.
	void Orbit(float InOrbit);

	// Raise\lower the pivot.
	void Pivot(float InPivot);

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
	UCameraComponent* CameraComponent{ nullptr };

	// Desired distance of the camera from the target, in world units.
	UPROPERTY(Category = Configuration, EditAnywhere)
	float CameraDistance{ 200.0f };

	// Desired vertical offset of the camera relative to its target, in world units.
	UPROPERTY(Category = Configuration, EditAnywhere)
	float CameraVerticalOffset{ 50.0f };

};

// ==================================================================== //
