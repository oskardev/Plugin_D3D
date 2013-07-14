// This sample will make your rendering window green, but you are free
// to do something more meaningfull ;)

#include <IPluginManager.h>
#include <IPluginD3D.h>
#include <d3d9.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include "CGPUMesh.h"
#include "IPluginInterfaces.h"

class CMyD3D
    : private D3DPlugin::ID3DEventListener//, public PluginManager::CPluginBase, public pluginInterfaces::IPluginInterfaces
{
protected:
	bool bDX9;
    bool bDX11;
    bool bExecuted;
    bool bMeshCanBeCreated;
    bool bDone;

	union device    // Declare union type
	{
		void* ptr;
		IDirect3DDevice9*	dx9;
		ID3D11Device*		dx11;
	} m_pDevice;

    PluginManager::IPluginBase* m_pD3DPlugin;
    D3DPlugin::IPluginD3D* m_pD3DSystem;
	IDirect3DStateBlock9* m_pStateBlock;

	void OnPrePresent() 
    {
        m_frame++;
        CryLog( "zomg OnPrePresent %d, %d", m_frame, bDone );
        if(false == bExecuted)
        {
            if ( 0 != gEnv->pGame)
            {
                if ( 0 != gEnv->pGame->GetIGameFramework()->GetClientActor() )
                {
                    CryLog( "zomg m_GPUMesh.init", 0 );
                    bMeshCanBeCreated = true;
                    //m_poGPUMesh->init();
                    bExecuted = true;
                }
            }
            else
            {

            }
        }
	};

	void OnPostPresent() 
    {

    };
	void OnPreReset() 
    {
		//SAFE_RELEASE(m_pStateBlock);
	};
	void OnPostReset() {};
	void OnPostBeginScene() {};

public:
    int m_frame;
    CGPUMesh* m_poGPUMesh;
	CMyD3D()
    {
        m_poGPUMesh = new CGPUMesh;
        bExecuted = false;
        bMeshCanBeCreated = false;
        bDone = false;
        m_frame = 0;
		m_pDevice.ptr	= NULL;
		m_pStateBlock	= NULL;

        m_pD3DPlugin = gPluginManager->GetPluginByName("D3D");

        m_pD3DSystem = static_cast<D3DPlugin::IPluginD3D*>(m_pD3DPlugin ? m_pD3DPlugin->GetConcreteInterface() : NULL);

		if(m_pD3DSystem)
		{
			// Initialize the device
			m_pDevice.ptr = m_pD3DSystem->GetDevice();
			bDX9 = false;
            bDX11 = true;

			//if(bDX9 && m_pDevice.ptr)
            if(bDX11 && m_pDevice.ptr)
			{ // Create D3D State [Optional: if you don't modify it]
				//m_pDevice.dx9->CreateStateBlock(D3DSBT_ALL, &m_pStateBlock);
                //m_pDevice.dx11->creates
			}

			// the listeners will be called renderer thread.
			m_pD3DSystem->RegisterListener(this);
		}
	};

	~CMyD3D() 
    {
		if(m_pD3DSystem)
        {
			m_pD3DSystem->UnregisterListener(this);
        }
		SAFE_RELEASE(m_pStateBlock);
	};

    //to use with IPluginInterfaces
    /*
    PluginManager::IPluginBase* GetBase()
    {
        return static_cast<PluginManager::IPluginBase*>( this );
    };

    void Update()
    {
        bDone = true;
        if(false != bMeshCanBeCreated)
        {
            m_poGPUMesh->init();
            bMeshCanBeCreated = false;
        }
        CryLogAlways( "zomg update executed" );
        return;
    };*/
};
