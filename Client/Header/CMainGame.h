#ifndef CMainGame_h__
#define CMainGame_h__

#include "CBase.h"
#include "Client_Include.h"

BEGIN(Engine)
class CGraphic_Device;
class CFontMgr;
class CManagement;
END

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
	Engine::CFontMgr* m_pFontMgr;
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
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};


#endif // !
