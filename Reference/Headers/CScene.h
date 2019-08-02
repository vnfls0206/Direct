#ifndef CScene_h__
#define CScene_h__

#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CScene abstract :
	public Engine::CBase
{
protected :
	explicit CScene(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CScene() = default;

private  :
	virtual HRESULT Initialize_Scene() = 0;
public :
	bool Is_End_Scene = false;
	virtual void Update_Scene(const float& fTimeDelta) = 0;
	virtual void Render_Scene() = 0;

private :
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;

protected :
	LPDIRECT3DDEVICE9 Get_Graphic_Device();

public:
	virtual void Free() override;

};

END
#endif