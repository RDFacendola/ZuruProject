
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"

#include "FreeCameraComponent.generated.h"

// ==================================================================== //

// Set of free camera actions.
//
// @author Raffaele D. Facendola - February 2021.
struct FFreeCameraActions
{
    // Movement of the camera, in world units.
    FVector2D Strafe{ FVector2D::ZeroVector };

    // Rotation of the camera around its target, in degrees.
    float Orbit{ 0.0f };

    // Raise or lower the camera with respect to its target, in degrees.
    float Pivot{ 0.0f };

    // Move the camera close or far aways from its target.
    float Distance{ 0.0f };

    // Switch to a top-view camera and snap.
    bool bTopView{ false };

    // Switch to a front-view camera and snap.
    bool bFrontView{ false };

    // Rotate the camera by 90 degrees clockwise and snap.
    bool bClockwise{ false };

    // Rotate the camera by 90 degrees counter-clockwise and snap.
    bool bCounterClockwise{ false };
};

// ==================================================================== //

/************************************************************************/
/* FREE CAMERA COMPONENT                                                */
/************************************************************************/

// A free camera component used to navigate the world from the above.
//
// The camera has four movements:
//
// Strafe: moves the camera in the XY plane.
// Orbit: orbit the camera around its target along the Z axis.
// Pivot: raise or lower the camera angle relative to its target.
// Distance: moves towards/away from the camera target.
//
// @author Raffaele D. Facendola - February 2021.
UCLASS()
class ZURURDF_API UFreeCameraComponent : public UCameraComponent
{
    GENERATED_BODY()

public:

    // Create a new free camera component.
    UFreeCameraComponent();

    // Set camera actions.
    void SetActions(const FFreeCameraActions& InCameraActions);

    // Advance the component status.
    void Advance(float InDeltaTime);

    // Get the target location.
    FVector GetLocation() const;

    // Get the target 2D location.
    FVector2D GetLocation2D() const;

    // Get the orbit angle of the camera relative to its target.
    FRotator GetOrbit() const;

    // Get the pivot angle of the camera relative to its target.
    float GetPivot() const;

    // Get the distance of the camera from its target.
    float GetDistance() const;

    // Get the minimum orbit value, in degrees.
    FRotator GetMinOrbit() const;

    // Get the maximum orbit value, in degrees.
    FRotator GetMaxOrbit() const;

    // Get the minimum pivot angle, in degrees.
    float GetMinPivot() const;

    // Get the minimum pivot angle, in degrees.
    float GetMaxPivot() const;

    // Get the minimum camera distance from its view target, in world units.
    float GetMinDistance() const;

    // Get the maximum camera distance from its view target, in world units.
    float GetMaxDistance() const;

    void BeginPlay() override;

private:
    
    // Update camera target movements.
    void IntegrateActions(float InDeltaTime);

    // Update actors and components to reflect latest component movements.
    void ApplyActions(float InDeltaTime);

    // Update camera transform.
    void SetCameraTransform(const FVector2D& InLocation, const FRotator& InOrbit, float InPivot, float InDistance, float InVerticalOffset);

    // Minimum angle between the camera and its target, in degrees.
    UPROPERTY(Category = Camera, EditAnywhere)
    float MinPivot{ 0.0f };

    // Maximum angle between the camera and its target, in degrees.
    UPROPERTY(Category = Camera, EditAnywhere)
    float MaxPivot{ 90.0f };
    
    // Initial camera pivot value, in degrees.
    UPROPERTY(Category = Camera, EditAnywhere)
    float DefaultPivot{ 60.0f };

    // Minimum distance of the camera from the target, in world units.
    UPROPERTY(Category = Camera, EditAnywhere)
    float MinDistance{ 100.0f };

    // Maximum distance of the camera from the target, in world units.
    UPROPERTY(Category = Camera, EditAnywhere)
    float MaxDistance{ 2000.0f };

    // Initial camera distance value, in world units. 
    UPROPERTY(Category = Camera, EditAnywhere)
    float DefaultDistance{ 1000.0f };

    // Desired vertical offset of the camera relative to its target, in world units.
    UPROPERTY(Category = Camera, EditAnywhere)
    float VerticalOffset{ 50.0f };

    // Movement speed, in world units per second.
    UPROPERTY(Category = Camera, EditAnywhere)
    float StrafeSpeed = { 10.0f };

    // Orbit speed, in degrees per second.
    UPROPERTY(Category = Camera, EditAnywhere)
    float OrbitSpeed = { 180.0f };

    // Pivot speed, in degrees per second.
    UPROPERTY(Category = Camera, EditAnywhere)
    float PivotSpeed{ 45.0f };

    // Distance speed, in distance percentage per second.
    UPROPERTY(Category = Camera, EditAnywhere)
    float DistanceSpeed{ 10.0f };

    // Movement smoothing speed. Zero to disable filtering.
    UPROPERTY(Category = Camera, EditAnywhere)
    float StrafeSmooth{ 0.0f };

    // Orbit smoothing speed. Zero to disable filtering.
    UPROPERTY(Category = Camera, EditAnywhere)
    float OrbitSmooth{ 0.0f };

    // Pivot smoothing speed. Zero to disable filtering.
    UPROPERTY(Category = Camera, EditAnywhere)
    float PivotSmooth{ 0.0f };

    // Distance smoothing speed. Zero to disable filtering.
    UPROPERTY(Category = Camera, EditAnywhere)
    float DistanceSmooth{ 0.0f };

    // Whether the camera target is the root of the actor (true) or the parent actor (false).
    UPROPERTY(Category = Camera, EditAnywhere)
    bool bTargetRoot{ true };

    // Current camera actions.
    FFreeCameraActions Actions;

    // Target camera location, in world units.
    FVector2D TargetLocation;

    // Target camera orbit, in degrees.
    FRotator TargetOrbit;

    // Target camera pivot, in degrees.
    float TargetPivot{ 0.0f };

    // Target camera distance, in world units.
    float TargetDistance{ 200.0f };

};

// ==================================================================== //
