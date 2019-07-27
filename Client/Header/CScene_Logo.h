#ifndef CScene_Logo_h__
#define CScene_Logo_h__

#include "CScene.h"

class CScene_Logo final :
	public Engine::CScene
{
private :
	explicit CScene_Logo(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CScene_Logo() = default;

	// CScene을(를) 통해 상속됨
private :
	virtual HRESULT Initialize_Scene() override;


public :
	// CScene을(를) 통해 상속됨
	virtual void Update_Scene(const float & fTimeDelta) override;
	virtual void Render_Scene() override;

public :
	static CScene_Logo* Create(LPDIRECT3DDEVICE9 pGraphic_Device);

public :
	virtual void Free() override;

};

#endif