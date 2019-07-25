#include "stdafx.h"
#include "CGameObject.h"
#include "CComponent_Manager.h"
USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pDevice(pGraphic_Device)
	, m_pComponentMgr(Engine::CComponent_Manager::GetInstance())
{

}
CGameObject::CGameObject(const CGameObject & rhs)
	: m_pDevice(rhs.m_pDevice)
{
	m_pDevice->AddRef();
}

HRESULT CGameObject::Initialize_GameObject()
{
	return E_NOTIMPL;
}

Engine::CComponent * CGameObject::Get_Component_In_Map(const TCHAR * pKey)
{
	if (pKey == nullptr) {
		return nullptr;
	}
	else if(!lstrcmp(pKey, L"")) {
		return nullptr;
	}
	if (m_mapComponent[pKey] == nullptr)
	{
		return nullptr;
	}

	return m_mapComponent[pKey];
}

void CGameObject::Free()
{
}
