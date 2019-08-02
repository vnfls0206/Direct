#ifndef CScene_Stage_h__
#define CScene_Stage_h__

#include "CScene.h"

BEGIN(Engine)
class CTimerMgr;
class CGameObject;
END

class CScene_Stage final :
	public Engine::CScene
{
private:
	explicit CScene_Stage(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CScene_Stage() = default;

	Engine::CTimerMgr* m_pTimerMgr;
	// CScene을(를) 통해 상속됨
private:
	virtual HRESULT Initialize_Scene() override;
	vector<Engine::CGameObject*> Good_GameObject_List;
	vector<Engine::CGameObject*> Evil_GameObject_List;
	vector<Engine::CGameObject*> ETC_GameObject_List;

	Engine::CGameObject* pPlayer = nullptr;


	Engine::CGameObject * Get_GameObject_From_List_By_Position
	(D3DXVECTOR3 Positon, vector<Engine::CGameObject*> p_List, int Begin);


public:
	// CScene을(를) 통해 상속됨
	virtual void Update_Scene(const float & fTimeDelta) override;
	virtual void Render_Scene() override;

public:
	static CScene_Stage* Create(LPDIRECT3DDEVICE9 pGraphic_Device);

public:
	virtual void Free() override;
};

#endif