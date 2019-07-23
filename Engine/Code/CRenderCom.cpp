#include "stdafx.h"
#include "CRenderCom.h"

Engine::CRenderCom::CRenderCom(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}
Engine::CRenderCom::CRenderCom(const CRenderCom & rhs)
	: CComponent(rhs)
{
	MSG_BOX("렌더러 컴포넌트는 복제가 불가능합니다..");
}

void Engine::CRenderCom::Add_GameObject_To_List(eRender_Sequence eState, Engine::CGameObject * pGameObject)
{
	if (pGameObject == nullptr)
		return;
	
	m_pList_Object[eState].push_back(pGameObject);
}

void Engine::CRenderCom::Render_RenderCom()
{
	for (int i = 0 ; i < eRender_Count; i++)
	{
		auto iter_begin = m_pList_Object[i].begin();
		auto iter_end = m_pList_Object[i].end();

		for (; iter_begin != iter_end; iter_begin++)
		{
			if ((*iter_begin) == nullptr) {
				MSG_BOX("렌더러 컴포넌트에 해제되지 않은 게임 오브젝트가 있습니다.");
				return;
			}
			(*iter_begin)->Render_GameObject();
		}
	}
	Clear_List();
}

Engine::CGameObject * Engine::CRenderCom::Check_GameObject_In_List_Overlapped(
	eRender_Sequence eState, Engine::CGameObject * pGameObject)
{
	auto iter_begin = m_pList_Object[eState].begin();
	auto iter_end = m_pList_Object[eState].end();

	for (; iter_begin != iter_end; iter_begin++)
	{
		if (*iter_begin == pGameObject)
		{
			return *iter_begin;
		}
	}
	return nullptr;
}




void Engine::CRenderCom::Clear_List()
{
	for (auto& pArray : m_pList_Object)
	{
		pArray.clear();
	}
}

Engine::CComponent * Engine::CRenderCom::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CRenderCom* pInstance = new CRenderCom(pGraphic_Device);
	return pInstance;
}

Engine::CComponent * Engine::CRenderCom::Clone()
{
	return this;
}
void Engine::CRenderCom::Free()
{
}
