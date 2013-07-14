#include <IIndexedMesh.h>
#include <IStatObj.h>

#pragma once

/**
 * @brief Stores mesh data
 */
class CGPUMesh
{
public:
    CGPUMesh();
    ~CGPUMesh();
    bool init();
    bool modifyMesh();
private:
    IStatObj* m_pObject;
    IIndexedMesh* m_pIndexedMesh;
    CMesh m_oMesh;
    IRenderMesh* m_pRenderMesh;
    IEntity* m_pEntity;
    SMeshSubset m_oSubset;
    float m_fpTimer;
    strided_pointer<Vec3> m_spVtx;
    int m_frame;
};
