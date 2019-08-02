#ifndef CScene_Stage_h__
#define CScene_Stage_h__

#include "Client_Include.h"
#include "CScene.h"

BEGIN(Engine)
class CTimerMgr;
class CGameObject;
class CLayer;
END

class CScene_Stage final :
	public Engine::CScene
{
private:
	explicit CScene_Stage(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CScene_Stage() = default;

	Engine::CTimerMgr* m_pTimerMgr;
	float m_fTimeAcc = 0.f;
	float m_fZoomRatio = 1.f;

	Engine::CLayer* m_vecAllylist;
	Engine::CLayer* m_vecEnemylist;
	Engine::CLayer* m_vecEtclist;
		   

private:
	//소멸된 객체를 벡터에서 지움
	void Delete_Empty_GameObject_In_vector();
	//공격 충돌판정 
	void Check_Attack();



	virtual HRESULT Initialize_Scene() override;
public:
	virtual void Update_Scene(const float & fTimeDelta) override;
	virtual void Render_Scene() override;

public:
	static CScene_Stage* Create(LPDIRECT3DDEVICE9 pGraphic_Device);

public:
	virtual void Free() override;
};

#endif