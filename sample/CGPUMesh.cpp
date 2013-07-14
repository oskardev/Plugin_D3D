#include <StdAfx.h>
#include "CGPUMesh.h"
#include <IGameObject.h>
#include <Actor.h>


CGPUMesh::CGPUMesh()
{
    m_fpTimer = 0.0f;
    m_pRenderMesh = 0;
    m_pEntity = 0;
    m_frame = 0;
}

CGPUMesh::~CGPUMesh()
{

}

bool CGPUMesh::init()
{
    CryLog( "CGPUMesh::init" );
    bool fRes = true;

    m_pObject = gEnv->p3DEngine->CreateStatObj();
    m_pObject->AddRef();
    m_pObject->Refresh( FRO_GEOMETRY );

    m_pIndexedMesh = m_pObject->GetIndexedMesh( true );
    m_oMesh.SetVertexCount( 3 );
    m_oMesh.SetFacesCount( 1 );
    m_oMesh.SetIndexCount( 3 );

    Vec3* vertices  = m_oMesh.GetStreamPtr<Vec3>( CMesh::POSITIONS );
    Vec3* normals   = m_oMesh.GetStreamPtr<Vec3>( CMesh::NORMALS );
    uint16* indices = m_oMesh.GetStreamPtr<uint16>( CMesh::INDICES );

    vertices[0] = Vec3( 1.0f, 1.0f, 0.0f );
    vertices[1] = Vec3( 0.0f, 5.0f, 0.0f );
    vertices[2] = Vec3( 5.0f, 1.0f, 0.0f );

    normals[0] = Vec3( 1, 0, 0 );
    normals[1] = Vec3( 1, 0, 0 );
    normals[2] = Vec3( 1, 0, 0 );

    indices[0] = 2;
    indices[1] = 1;
    indices[2] = 0;

    m_oSubset.nFirstIndexId = 0;
    m_oSubset.nFirstVertId = 0;
    m_oSubset.nNumIndices = 3;
    m_oSubset.nNumVerts = 3;
    
    m_oMesh.m_subsets.push_back( m_oSubset );
    m_oMesh.m_bbox = m_pObject->GetAABB();

    const char* ppErrorDesc;
    assert( m_oMesh.Validate( &ppErrorDesc ) );

    m_pIndexedMesh->SetMesh( m_oMesh );
    m_pIndexedMesh->Invalidate();

    m_pRenderMesh = m_pObject->GetRenderMesh();
    m_pRenderMesh->SetMesh( m_oMesh );


    m_pEntity = gEnv->pGame->GetIGameFramework()->GetClientActor()->GetEntity();
    m_pEntity->Activate ( true );
    
    //int slotCount = m_pEntity->GetSlotCount();
    int slotId = m_pEntity->SetStatObj( m_pObject, -1, false );
    //int slotCount2 = m_pEntity->GetSlotCount();
    CryLog( "CGPUMesh - Mesh Created %d", 0 );

    return fRes;
}

bool CGPUMesh::modifyMesh()
{
    return true;
}
