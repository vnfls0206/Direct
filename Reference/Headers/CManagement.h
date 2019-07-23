#ifndef CManagement_h__
#define CManagement_h__

#include "CBase.h"
#include "CGameObject_Manager.h"


BEGIN(Engine)
class CScene;
class CRenderCom;

class ENGINE_DLL CManagement final :		// �� Ŭ������, ���� ���� �����ϰų�, ���� ���� �������Ϻ����٤�;��
	public Engine::CBase
{
	DECLARE_SINGLETON(CManagement)
private :
	explicit CManagement();
	virtual ~CManagement() = default;

public :
	HRESULT SetUp_CurrentScene(int iSceneID, Engine::CScene* pScene);
	void Update_CurrentScene(const float& fTimeDelta);
	void Render_CurrentScene();

private :
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	Engine::CScene* m_pCurrentScene = nullptr;
	int m_iScene_ID = 0;

private :
	Engine::CGameObject_Manager* m_pGameObj_Mgr = nullptr;

private:
	Engine::CRenderCom* m_pRenderCom = nullptr;

public :
	virtual void Free() override;
};


END
#endif