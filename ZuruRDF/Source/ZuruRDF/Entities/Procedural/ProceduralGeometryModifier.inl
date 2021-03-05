
// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY MODIFIER STREAM                                  */
/************************************************************************/

template <typename TProceduralGeometryModifier>
template <typename UProceduralGeometryModifier>
FProceduralGeometryModifierStream<TProceduralGeometryModifier>::FProceduralGeometryModifierStream(FProceduralGeometryStream& InProceduralGeometryStream, UProceduralGeometryModifier&& InProceduralGeometryModifier)
    : ProceduralGeometryModifier(Forward<UProceduralGeometryModifier>(InProceduralGeometryModifier))
    , ProceduralGeometryStream(&InProceduralGeometryStream)
{
    ProceduralGeometryModifier.Bind(*ProceduralGeometryStream);
}

template <typename TProceduralGeometryModifier>
template <typename UProceduralGeometryModifier, typename>
FProceduralGeometryModifierStream<TProceduralGeometryModifier>::FProceduralGeometryModifierStream(FProceduralGeometryModifierStream<UProceduralGeometryModifier>&& InRHS)
    : ProceduralGeometryModifier(MoveTempIfPossible(InRHS.ProceduralGeometryModifier))
    , ProceduralGeometryStream(InRHS.ProceduralGeometryStream)
{

}

template <typename TProceduralGeometryModifier>
FProceduralGeometryModifierStream<TProceduralGeometryModifier>::~FProceduralGeometryModifierStream()
{
    if (ProceduralGeometryStream)
    {
        ProceduralGeometryModifier.Unbind(*ProceduralGeometryStream);
    }
}

template <typename TProceduralGeometryModifier>
template <typename UProceduralGeometryModifier, typename>
FProceduralGeometryModifierStream<TProceduralGeometryModifier>& FProceduralGeometryModifierStream<TProceduralGeometryModifier>::operator=(FProceduralGeometryModifierStream<UProceduralGeometryModifier>&& InRHS)
{
    Swap(ProceduralGeometryModifier, InRHS.ProceduralGeometryModifier);
    Swap(ProceduralGeometryStream, InRHS.ProceduralGeometryStream);

    return *this;
}

template <typename TProceduralGeometryModifier>
void FProceduralGeometryModifierStream<TProceduralGeometryModifier>::AppendVertex(const FProceduralVertex& InVertex)
{
    ProceduralGeometryModifier.AppendVertex(InVertex, *ProceduralGeometryStream);
}

template <typename TProceduralGeometryModifier>
const FProceduralVertex& FProceduralGeometryModifierStream<TProceduralGeometryModifier>::GetVertex(int32 InIndex) const
{
    return ProceduralGeometryStream->GetVertex(InIndex);
}

template <typename TProceduralGeometryModifier>
int32 FProceduralGeometryModifierStream<TProceduralGeometryModifier>::GetVertexCount() const
{
    return ProceduralGeometryStream->GetVertexCount();
}

/************************************************************************/
/* NON-MEMBER FUNCTIONS                                                 */
/************************************************************************/

template <typename TProceduralGeometryModifier, typename>
FProceduralGeometryModifierStream<TProceduralGeometryModifier> operator<<(FProceduralGeometryStream& OutProceduralGeometryStream, TProceduralGeometryModifier&& InProceduralGeometryModifier)
{
    return FProceduralGeometryModifierStream<TProceduralGeometryModifier>{ OutProceduralGeometryStream, Forward<TProceduralGeometryModifier>(InProceduralGeometryModifier) };
}

template <typename TProceduralGeometryModifier, typename>
FProceduralGeometryModifierStream<TProceduralGeometryModifier> operator<<(FProceduralGeometryStream&& OutProceduralGeometryStream, TProceduralGeometryModifier&& InProceduralGeometryModifier)
{
    return FProceduralGeometryModifierStream<TProceduralGeometryModifier>{ OutProceduralGeometryStream, Forward<TProceduralGeometryModifier>(InProceduralGeometryModifier) };
}

// ==================================================================== //
