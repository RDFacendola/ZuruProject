
// ==================================================================== //

#pragma once

#include "CoreMinimal.h"

#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Templates/UnrealTypeTraits.h"

#include "ProceduralGeometryStream.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY MODIFIER                                         */
/************************************************************************/

// Base interface for functors that bind to a geometry stream and apply a custom function to vertex passed through.
// Modifiers can also be used either to add or remove geometries procedurally.
//
// @author Raffaele D. Facendola - March 2021.
struct ZURURDF_API FProceduralGeometryModifier
{
public:

    // Default virtual destructor.
    virtual ~FProceduralGeometryModifier() = default;

    // Bind the modifier to a geometry stream.
    virtual void Bind(FProceduralGeometryStream& OutProceduralGeometryStream) = 0;

    // Called whenever a vertex is appended to a procedural geometry stream.
    virtual void AppendVertex(const FProceduralVertex& InVertex, FProceduralGeometryStream& OutProceduralGeometryStream) = 0;

    // Unbind the modifier from a geometry stream.
    virtual void Unbind(FProceduralGeometryStream& OutProceduralGeometryStream) = 0;

};

/************************************************************************/
/* PROCEDURAL GEOMETRY MODIFIER STREAM                                  */
/************************************************************************/

// A decorator that forwards procedurally-generated geometry to an underlying
// geometry stream through a modifier function.
//
// @remarks This class is an implementation detail and shall not be used directly.
// @see operator<<(FProceduralGeometryStream, FProceduralGeometryModifier).
// 
//
// @author Raffaele D. Facendola - March 2021.
template <typename TProceduralGeometryModifier>
struct ZURURDF_API FProceduralGeometryModifierStream : public FProceduralGeometryStream
{
public:

    // Decorate a procedural geometry stream with a modifier.
    template <typename UProceduralGeometryModifier>
    FProceduralGeometryModifierStream(FProceduralGeometryStream& InProceduralGeometryStream, UProceduralGeometryModifier&& InProceduralGeometryModifier);

    // Default copy-constructor.
    FProceduralGeometryModifierStream(const FProceduralGeometryModifierStream& InRHS) = default;

    // Move-constructor.
    // This function participates in overload resolution only if TProceduralGeometryModifier is move-constructible.
    template <typename UProceduralGeometryModifier = TProceduralGeometryModifier,
              typename = TEnableIf<std::is_move_constructible<UProceduralGeometryModifier>::value>::Type>
    FProceduralGeometryModifierStream(FProceduralGeometryModifierStream<UProceduralGeometryModifier>&& InRHS);

    // Virtual destructor.
    virtual ~FProceduralGeometryModifierStream();

    // Default copy-assignment operator.
    FProceduralGeometryModifierStream& operator=(const FProceduralGeometryModifierStream& InRHS) = default;

    // Move-assignment operator.
    // This function participates in overload resolution only if TProceduralGeometryModifier is move-assignable.
    template <typename UProceduralGeometryModifier = TProceduralGeometryModifier,
              typename = TEnableIf<std::is_move_assignable<UProceduralGeometryModifier>::value>::Type>
    FProceduralGeometryModifierStream& operator=(FProceduralGeometryModifierStream<UProceduralGeometryModifier>&& InRHS);

    virtual void AppendVertex(const FProceduralVertex& InVertex) override;

    virtual const FProceduralVertex& GetVertex(int32 InIndex) const override;

    virtual int32 GetVertexCount() const override;

private:

    // Procedural geometry modifier.
    TProceduralGeometryModifier ProceduralGeometryModifier;

    // Underlying geometry stream.
    FProceduralGeometryStream* ProceduralGeometryStream{ nullptr };

};

/************************************************************************/
/* NON-MEMBER FUNCTIONS                                                 */
/************************************************************************/

// Bind a procedural geometry modifier to a procedural geometry stream.
// This method participates in overload resolution only if FProceduralGeometryModifier is a base class for TProceduralGeometryModifier.
//
// @usage FProceduralGeometryStream& FGS = ...;
//        FGS << FProceduralGeometryModifierDerivate{ ... }
//            << meshes \ modifiers;
//
template <typename TProceduralGeometryModifier,
          typename = TEnableIf<TIsDerivedFrom<TDecay<TProceduralGeometryModifier>::Type,
                                              FProceduralGeometryModifier>::Value>::Type>
FProceduralGeometryModifierStream<TProceduralGeometryModifier> operator<<(FProceduralGeometryStream& OutProceduralGeometryStream, TProceduralGeometryModifier&& InProceduralGeometryModifier);

// Bind a procedural geometry modifier to a procedural geometry stream.
// This method participates in overload resolution only if FProceduralGeometryModifier is a base class for TProceduralGeometryModifier.
//
// @usage FProceduralGeometryStream& FGS = ...;
//        FGS << FProceduralGeometryModifierDerivate{ ... }
//            << meshes \ modifiers;
//
template <typename TProceduralGeometryModifier,
          typename = TEnableIf<TIsDerivedFrom<TDecay<TProceduralGeometryModifier>::Type,
                                              FProceduralGeometryModifier>::Value>::Type>
FProceduralGeometryModifierStream<TProceduralGeometryModifier> operator<<(FProceduralGeometryStream&& OutProceduralGeometryStream, TProceduralGeometryModifier&& InProceduralGeometryModifier);

// ==================================================================== //

#include "ProceduralGeometryModifier.inl"

// ==================================================================== //
