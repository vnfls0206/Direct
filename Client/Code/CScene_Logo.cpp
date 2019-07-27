#include "stdafx.h"
#include "CScene_Logo.h"
#include "CScene_Stage.h"

#include "Client_Enum.h"
#include "CVideo_Manager.h"
#include "CManagement.h"



CScene_Logo::CScene_Logo(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CScene(pGraphic_Device)
{
}

HRESULT CScene_Logo::Initialize_Scene()
{
	CVideo_Manager::GetInstance()->Ready_Video();
	CVideo_Manager::GetInstance()->Play_Video();

	return NOERROR;
}

void CScene_Logo::Update_Scene(const float & fTimeDelta)
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		Is_End_Scene = true;
	}

	return;
}

void CScene_Logo::Render_Scene()
{
	return;
}

CScene_Logo * CScene_Logo::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CScene_Logo* pInstance = new CScene_Logo(pGraphic_Device);
	if (FAILED(pInstance->Initialize_Scene()))
	{
		MSG_BOX("로고 씬 실행 실패");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Logo::Free()
{
	CVideo_Manager::GetInstance()->DestroyInstance();
	return;
}
