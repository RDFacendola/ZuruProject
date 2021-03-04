
// ==================================================================== //

#include "ProceduralMesh.h"

// ==================================================================== //

/************************************************************************/
/* PROCEDURAL GEOMETRY MESH                                             */
/************************************************************************/

void FProceduralMesh::AppendTo(FProceduralGeometryStream& OutGeometryStream) const
{
    // Virtual call.

    Build(OutGeometryStream);

    // Check if the geometry stream contains an integer amount of triangles and, if not,
    // close the list to prevent the remaining geometry to be affected.

    auto VertexCount = OutGeometryStream.GetVertexCount();
    auto MissingVerticesCount = VertexCount % 3;

    ensure(MissingVerticesCount == 0);

    for (auto Index = 0; Index < MissingVerticesCount; ++Index)
    {
        OutGeometryStream.AppendVertex(OutGeometryStream.GetVertex(-1));
    }
}

// ==================================================================== //

/************************************************************************/
/* NON-MEMBER FUNCTIONS                                                 */
/************************************************************************/

FProceduralGeometryStream& operator<<(FProceduralGeometryStream& OutGeometryStream, const FProceduralMesh& InItem)
{
    InItem.AppendTo(OutGeometryStream);

    return OutGeometryStream;
}

// ==================================================================== //

