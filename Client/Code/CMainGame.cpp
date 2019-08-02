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
#include "CMonster.h"
#include "CBack.h"
#include "Enemy.h"
#include "CUI_Card.h"

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
	m_pTimerMgr(Engine::CTimerMgr::GetInstance()),
	m_pDevice(nullptr)
{
	m_pGameObject->AddRef();
	m_pComponentMgr->AddRef();
}

HRESULT CMainGame::Initialize_CMainGame()
{
	if (FAILED(m_pGraphic_Device->Intialize_CGraphic_Device(g_hWnd, m_pGraphic_Device->eWInMode, WINCX, WINCY, &m_pDevice)))
	{
		MSG_BOX("����̽� �ʱ�ȭ�� �����Ͽ����ϴ�!");
		return E_FAIL;
	}
	
	m_pFontMgr->Add_Font(m_pDevice, 10, 10, FW_LIGHT, L"����");

	m_pGameObject->Reserve_Proto_Layer_Array(eScene_Count);

	m_pComponentMgr->Add_Component_In_Map(L"Component_Transform",
		Engine::CTransform::Create(m_pDevice));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Texture_Player",
		Engine::CTexture::Create(m_pDevice, L"../../Resource/Player/Move/Back/", L".png", 0, 5));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Texture_Enemy",
		Engine::CTexture::Create(m_pDevice, L"../../Resource/Player/", L".png", 0, 0));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Texture_Rinel",
		Engine::CTexture::Create(m_pDevice, L"../../Resource/Rinel/", L".png", 0, 82));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Texture_Back",
		Engine::CTexture::Create(m_pDevice, L"../../Resource/Back/", L".dds", 0, 0));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Texture_UI_Card",
		Engine::CTexture::Create(m_pDevice, L"../../Resource/UI/Card/", L".png", 0, 6));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Buffer_RcTex",
		Engine::CBuffer_RcTex::Create(m_pDevice));

	m_pComponentMgr->Add_Component_In_Map(L"Component_RenderCom",
		Engine::CRenderCom::Create(m_pDevice));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Shader_Default",
		Engine::CShader::Create(m_pDevice, L"../../Reference/Shaders/Shader_Default.fx"));

	m_pComponentMgr->Add_Component_In_Map(L"Component_Collider",
		Engine::CCollider::Creat(m_pDevice));


	Engine::DESC_PROJ tagProj = {WINCX, WINCY, 1.f, 100.f};
	Engine::DESC_VIEW tagView = {D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,0,0),D3DXVECTOR3(0,1,0)};

	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_StaticCamera", CStatic_Camera::Create(m_pDevice, tagView, tagProj));
	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_Player", CPlayer::Create(m_pDevice));
	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_Enemy", Enemy::Create(m_pDevice));

	MON_INFO Rinel_Info = { {{ 0.5f, 8, 15 }, { 0.5f, 24, 31 }, { 0.5f, 16, 23 }, { 0.5f, 0, 7 },
							 { 0.5f, 37, 41 }, { 0.5f, 47, 51 }, { 0.5f, 42, 46 }, { 0.5f, 32, 36 },
							 { 0.5f, 60, 66 }, { 0.5f, 75, 82 }, { 0.5f, 67, 74 }, { 0.5f, 52, 59 }}, 300, 150 };


	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_Rinel", CMonster::Create(m_pDevice, Rinel_Info));

	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_Back", CBack::Create(m_pDevice));
	m_pGameObject->Insert_Prototype_GameObject_To_ProtoMap((int)eScene_Static,
		L"GameObject_Proto_UI_Card", CUI_Card::Create(m_pDevice));

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
		wsprintf(m_szFPS, L"FPS : %d", m_iRenderCnt);
		m_iRenderCnt = 0;
		m_fTImeAcc = 0.f;
	}


	if (m_eSceneState != eScene_Logo) 
	{
		m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
			D3DXCOLOR(0.f, 0.f, 1.f, 1.f), 1.f, 0);
		m_pDevice->BeginScene();


		m_pManagement->Render_CurrentScene();

		POINT pt = { 0,20 };
		m_pFontMgr->Render_Font(L"����", m_szFPS, pt, D3DCOLOR_ARGB(255, 83, 223, 214));

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
		MSG_BOX("����̽� ��������!");
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
	m_pTimerMgr->DestroyInstance();

	Engine::Safe_Release(m_pDevice);
}
