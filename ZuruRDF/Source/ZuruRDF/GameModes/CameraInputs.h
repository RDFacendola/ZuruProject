
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

// ==================================================================== //

/************************************************************************/
/* CAMERA INPUTS                                                        */
/************************************************************************/

// Exposes camera-relevant inputs.
//
// @author Raffaele D. Facendola - February 2021.
struct ZURURDF_API FCameraInputs
{
	// Name of the axis used to orbit the camera around its target.
	static const FName kCameraOrbit;

	// Name of the axis used to move the camera forwards\backwards on the world XY plane.
	static const FName kCameraForward;

	// Name of the axis used to move the camera left\right on the world XY plane.
	static const FName kCameraRight;

	// Name of the axis used to tilt the camera above\below its target up to 90 degrees.
	static const FName kCameraPivot;
};

// ==================================================================== //
