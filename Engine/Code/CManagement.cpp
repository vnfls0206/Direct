#include "stdafx.h"
#include "CManagement.h"
#include "CScene.h"

#include "CComponent_Manager.h"
#include "CRenderCom.h"

IMPLEMENT_SINGLETON(Engine::CManagement)

Engine::CManagement::CManagement()
	: m_pCurrentScene(nullptr), m_pDevice(nullptr),
	m_pGameObj_Mgr(Engine::CGameObject_Manager::GetInstance())
{
}

HRESULT Engine::CManagement::SetUp_CurrentScene(int iSceneID , Engine::CScene * pScene)
{
	if (pScene == nullptr) {
		MSG_BOX("매니지먼트 클래스에서, 현재 씬을 스왑하려는 도중, 매개변수로, NULLPTR 가 들어왔습니다!");
		return E_FAIL;
	}

	if(m_pCurrentScene != nullptr)
		Engine::Safe_Release(m_pCurrentScene);

	m_pRenderCom = dynamic_cast<Engine::CRenderCom*>(
		Engine::CComponent_Manager::GetInstance()->Get_Component_In_Map_By_Proto(L"Component_RenderCom"));

	m_pCurrentScene = pScene;
	m_iScene_ID = iSceneID;

	return NOERROR;
}

void Engine::CManagement::Update_CurrentScene(const float & fTimeDelta)
{
	m_pGameObj_Mgr->Update_Layers(m_iScene_ID, fTimeDelta);
	m_pCurrentScene->Update_Scene(fTimeDelta);
}

void Engine::CManagement::Render_CurrentScene()
{
	m_pRenderCom->Render_RenderCom();
	m_pCurrentScene->Render_Scene();
}

void Engine::CManagement::Free()
{
	Engine::Safe_Release(m_pCurrentScene);
}
