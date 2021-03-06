
// ==================================================================== //

#include "ChairEntity.h"

#include "Procedural/ProceduralGeometryStream.h"
#include "Procedural/ProceduralMesh.h"
#include "Procedural/ProceduralQuad.h"
#include "Procedural/ProceduralNullModifier.h"
#include "Procedural/ProceduralIdentityModifier.h"
#include "Procedural/ProceduralTranslateModifier.h"
#include "Procedural/ProceduralRotateModifier.h"
#include "Procedural/ProceduralScaleModifier.h"
#include "Procedural/ProceduralMirrorModifier.h"
#include "Procedural/ProceduralExtrudeModifier.h"

// ==================================================================== //

PRAGMA_DISABLE_OPTIMIZATION

struct FProceduralMeshBuilder : public FProceduralGeometryStream
{
public:

    FProceduralMeshBuilder() = default;

    virtual ~FProceduralMeshBuilder() = default;

    virtual FProceduralGeometryStream& AppendVertex(const FProceduralVertex& InVertex) override
    {
        Vertices.Emplace(InVertex);

        return *this;
    }

    virtual const FProceduralVertex& GetVertex(int32 InIndex) const override
    {
        if (InIndex >= 0)
        {
            return Vertices[InIndex];                       // Forward.
        }
        else
        {
            return Vertices[Vertices.Num() + InIndex];      // Reverse.
        }
    }

    virtual int32 GetVertexCount() const override
    {
        return Vertices.Num();
    }

// private:

    TArray<FProceduralVertex> Vertices;

};

/************************************************************************/
/* CHAIR ENTITY                                                         */
/************************************************************************/

AChairEntity::AChairEntity()
{
    // Root component.

    ProceduralComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Root"));

    SetRootComponent(ProceduralComponent);
}

void AChairEntity::BeginPlay()
{
    Super::BeginPlay();
    
    auto ProceduralMeshBuilder = FProceduralMeshBuilder{};

    ProceduralMeshBuilder << FProceduralExtrudeModifier{ FVector::UpVector * 100.0f }
                          << FProceduralQuad{ { 100.0f, 100.0f } };

    // Convert to Unreal procedural mesh component.

    auto Vertices = TArray<FVector>{};
    auto Normals = TArray<FVector>{};
    auto UVs = TArray<FVector2D>{};
    auto Indices = TArray<int32>{};

    Vertices.Reserve(ProceduralMeshBuilder.GetVertexCount());
    Normals.Reserve(ProceduralMeshBuilder.GetVertexCount());
    UVs.Reserve(ProceduralMeshBuilder.GetVertexCount());
    Indices.Reserve(ProceduralMeshBuilder.GetVertexCount());

    for (auto&& Vertex : ProceduralMeshBuilder.Vertices)
    {
        Vertices.Emplace(Vertex.Position);
        Normals.Emplace(Vertex.Normal);
        UVs.Emplace(Vertex.UV);
        Indices.Emplace(Indices.Num());
    }

    ProceduralComponent->ClearAllMeshSections();
    ProceduralComponent->CreateMeshSection(0, Vertices, Indices, Normals, UVs, TArray<FColor>{}, TArray<FProcMeshTangent>{}, false);
    ProceduralComponent->SetMaterial(0, Material);
}

PRAGMA_ENABLE_OPTIMIZATION

// ==================================================================== //

