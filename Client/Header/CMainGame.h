#ifndef CMainGame_h__
#define CMainGame_h__

#include "CBase.h"
#include "Client_Include.h"

BEGIN(Engine)
class CGraphic_Device;
class CGameObject_Manager;
class CComponent_Manager;
class CFontMgr;
class CManagement;
class CKeyManager;
class CTimerMgr;
END
class CSound_Manager;		//Engine æ∆¥‘

class CMainGame final :
	public Engine::CBase
{
	private :
		explicit CMainGame();
		virtual ~CMainGame() = default;

private :
	HRESULT Initialize_CMainGame();
public :
	int Update(const float& fTimeDelta);
	void Render();

private :
	HRESULT Swap_Scene(eSceneState eState);

public :
	static CMainGame* Create();

private :
	Engine::CManagement* m_pManagement;
	Engine::CGraphic_Device* m_pGraphic_Device;
	Engine::CGameObject_Manager* m_pGameObject;
	Engine::CComponent_Manager* m_pComponentMgr;
	Engine::CFontMgr* m_pFontMgr;
	Engine::CKeyManager* m_pCKeyMgr;
	Engine::CTimerMgr* m_pTimerMgr;
	CSound_Manager* m_pSoundMgr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;

private :
	TCHAR			m_szKey[50];
	TCHAR			m_szFPS[128] = L"";
	int m_iRenderCnt = 0;
	float m_fTImeAcc = 0.f;

private :
	eSceneState	m_eSceneState;

private :
	bool		m_bFlag = false;

public :
	// CBase¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual void Free() override;
};


#endif // !
