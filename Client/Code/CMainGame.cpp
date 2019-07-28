#pragma region Headers
#include "stdafx.h"
#include "CMainGame.h"
#include "CGraphic_Device.h"
#include "CManagement.h"
#include "CFontMgr.h"
#include "CFrameMgr.h"
#include "CTimerMgr.h"

#include "CGameObject_Manager.h"
#include "CComponent_Manager.h"
#include "CGraphic_Device.h"
#include "CKeyManager.h"
#include "CSound_Manager.h"

#include "CTransform.h"
#include "CShader.h"
#include "CTexture.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"
#include "CCollider.h"

#include "CStatic_Camera.h"
#include "CPlayer.h"
#include "CBack.h"
#include "Enemy.h"


#include "CScene_Logo.h"
#include "CScene_Stage.h"


#pragma endregion 


CMainGame::CMainGame()
	: m_pGraphic_Device(Engine::CGraphic_Device::GetInstance()),
	m_pManagement(Engine::CManagement::GetInstance()),
	m_pGameObject(Engine::CGameObject_Manager::GetInstance()),
	m_pComponentMgr(Engine::CComponent_Manager::GetInstance()),
	m_pFontMgr(Engine::CFontMgr::GetInstance()),
	m_pCKeyMgr(Engine::CKeyManager::GetInstance()),
	m_pSoundMgr(CSound_Manager::GetInstance()),
	m_pDevice(nullptr)
{
	m_pGameObject->AddRef();
	m_pComponentMgr->AddRef();
}

HRESULT CMainGame::Initialize_CMainGame()
{
	if (FAILED(m_pGraphic_Device->Intialize_CGraphic_Device(g_hWnd, m_pGraphic_Device->eWInMode, WINCX, WINCY, &m_pDevice)))
	{
		MSG_BOX("디바이스 초기화가 실패하였습니다!");
		return E_FAIL;
	}

	lstrcpy(m_szKey, L"굴림");
	m_pFontMgr->Add_Font(m_pDevice, 20, 50, FW_BOLD, m_szKey);



	//LPDIRECT3DDEVICE9 pGrpahicDev = Engine::CGraphic_Device::GetInstance()->Get_Graphic_Device();

	m_pGameObject->Reserve_Proto_Layer_Array(eScene_Count);

	m_pComponentMgr->Add_Component_In_Map(L"Component_Transform",
		Engine::CTransform::Create(m_pDevice));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Texture_Player",
		Engine::CTexture::Create(m_pDevice, L"../../Resource/Player/", L".png", 0, 2));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Texture_Enemy",
		Engine::CTexture::Create(m_pDevice, L"../../Resource/Player/", L".png", 0, 0));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Texture_Back",
		Engine::CTexture::Create(m_pDevice, L"../../Resource/Back/", L".dds", 0, 0));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Buffer_RcTex",
		Engine::CBuffer_RcTex::Create(m_pDevice));

	m_pComponentMgr->Add_Component_In_Map(L"Component_RenderCom",
		Engine::CRenderCom::Create(m_pDevice));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Shader_Default",
		Engine::CShader::Create(m_pDevice, L"../../Reference/Shaders/Shader_Default.fx"));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Collider",
		Engine::CCollider::Creat(m_pDevice));


	Engine::DESC_PROJ tagProj = {WINCX, WINCY, 1.f, 1000.f};
	Engine::DESC_VIEW tagView = {D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,1,0)};

	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_StaticCamera", CStatic_Camera::Create(m_pDevice, tagView, tagProj));

	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_Player", CPlayer::Create(m_pDevice));
	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_Enemy", Enemy::Create(m_pDevice));
	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_Back", CBack::Create(m_pDevice));

	Engine::Safe_Release(m_pGameObject);
	Engine::Safe_Release(m_pComponentMgr);

	m_eSceneState = eScene_Logo;
	Swap_Scene(eScene_Logo);

	return S_OK;
}
int CMainGame::Update(const float& fTimeDelta)
{
	if (m_pManagement->Check_CurrentScene_End())
	{
		m_eSceneState = (eSceneState)(m_eSceneState + 1);
		Swap_Scene(m_eSceneState);
	}

	m_fTImeAcc += fTimeDelta;

	m_pManagement->Update_CurrentScene(fTimeDelta);

	m_pCKeyMgr->Update();
	m_pSoundMgr->Update();
	return 0;
}


void CMainGame::Render()
{
	if (m_pDevice == nullptr)
		return;

	++m_iRenderCnt;
	if (m_fTImeAcc >= 1.f)
	{
		wsprintf(m_szFPS, L"에프피에스 : %d", m_iRenderCnt);
		m_iRenderCnt = 0;
		m_fTImeAcc = 0.f;
	}
	SetWindowText(g_hWnd, m_szFPS);


	if (m_eSceneState != eScene_Logo) 
	{
		m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
			D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);
		m_pDevice->BeginScene();


		m_pManagement->Render_CurrentScene();

		POINT pt = { 0,20 };
		m_pFontMgr->Render_Font(m_szKey, m_szFPS, pt, D3DCOLOR_ARGB(255, 0, 255, 0));

		m_pDevice->EndScene();
		m_pDevice->Present(nullptr, nullptr, g_hWnd, nullptr);
	}

}

HRESULT CMainGame::Swap_Scene(eSceneState eState)
{
	switch (eState)
	{
	case eScene_Logo :
		m_pManagement->SetUp_CurrentScene(eScene_Logo, CScene_Logo::Create(m_pDevice));
		break;
	case eScene_Stage1 :
		m_pManagement->SetUp_CurrentScene(eScene_Stage1, CScene_Stage::Create(m_pDevice));
		break;
	}

	return E_NOTIMPL;
}



CMainGame * CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame();
	if (FAILED(pInstance->Initialize_CMainGame()))
	{
		MSG_BOX("디바이스 생성실패!");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainGame::Free()
{
	Engine::CTimerMgr::GetInstance()->DestroyInstance();
	Engine::CFrameMgr::GetInstance()->DestroyInstance();

	m_pFontMgr->DestroyInstance();
	m_pManagement->DestroyInstance();
	m_pCKeyMgr->DestroyInstance();
	m_pGameObject->DestroyInstance();
	m_pComponentMgr->DestroyInstance();
	m_pSoundMgr->DestroyInstance();

	Engine::Safe_Release(m_pDevice);
}
