#include "stdafx.h"
#include "CLayer.h"


Engine::CLayer * Engine::CLayer::Create()
{
	Engine::CLayer* pInstance = new Engine::CLayer();

	return pInstance;
}

void Engine::CLayer::Insert_GameObject_To_Layer(Engine::CGameObject* pGameObject)
{
	m_pList_GameObject.push_back(pGameObject);
	m_uiListSize++;
}
bool Engine::CLayer::Find_OverLapped_GameObject_In_Layer(const Engine::CGameObject* pGameObject)
{
	return false;
}
void Engine::CLayer::Delete_GameObject_In_Layer(const int iObjectIndex)
{
	int iStartIndex = 0;

	auto iter_end = m_pList_GameObject.end();
	for (auto iter_begin = m_pList_GameObject.begin();
		iter_end != iter_begin; iter_begin++, iStartIndex++)
	{
		if (iStartIndex == iObjectIndex) {
			iter_begin = m_pList_GameObject.erase(iter_begin);
			m_uiListSize--;
			return;
		}
	}
}

int Engine::CLayer::Get_List_Size(){return m_uiListSize;}

Engine::CGameObject * Engine::CLayer::Get_GameObject_In_List(const int iIndex)
{
	auto iter_begin = m_pList_GameObject.begin();
	auto iter_end = m_pList_GameObject.end();

	int index = 0;
	for (; iter_begin != iter_end; iter_begin++)
	{
		if (*iter_begin == nullptr)
		{
			//(*iter_begin)->Free();
			m_pList_GameObject.erase(iter_begin);
			m_uiListSize--;

		}
		if (index == iIndex)
		{
			return *iter_begin;
		}
		else
			index++;
	}
	return nullptr;
}

void Engine::CLayer::Update_Layer(const float & fTimeDelta)
{
	if (m_pList_GameObject.empty()) {
		return;
	}
	/*
	int iCount = 0;
	auto iter_begin = m_pList_GameObject.begin();
	auto iter_end = m_pList_GameObject.end();

	while (iter_begin != iter_end)
	{
		if (*iter_begin == nullptr)
		{
			m_pList_GameObject.erase(iter_begin);
			iter_begin = m_pList_GameObject.begin();
			iter_end = m_pList_GameObject.end();
			for (int i = 0; i < iCount; i++)
			{
				iter_begin++;
			}
		}
		(*iter_begin)->Update_GameObject(fTimeDelta);

		iter_begin++;
		iCount++;
	}

	iCount = 0;
	iter_begin = m_pList_GameObject.begin();
	iter_end = m_pList_GameObject.end();
	while (iter_begin != iter_end)
	{
		if (*iter_begin == nullptr)
		{
			m_pList_GameObject.erase(iter_begin);
			iter_begin = m_pList_GameObject.begin();
			iter_end = m_pList_GameObject.end();
			for (int i = 0; i < iCount; i++)
			{
				iter_begin++;
			}
		}
		(*iter_begin)->LastUpdate_GameObject(fTimeDelta);

		iter_begin++;
		iCount++;
	}*/
	
	for (auto& pInstance : m_pList_GameObject) {
		if(pInstance == nullptr)
		{
			return;
		}
		pInstance->Update_GameObject(fTimeDelta);
	}
	for (auto& pInstance : m_pList_GameObject) {
		if (pInstance == nullptr)
		{
			return;
		}
		pInstance->LastUpdate_GameObject(fTimeDelta);
	}
	
	return;
}

void Engine::CLayer::Free()
{
	for (auto& pInstance : m_pList_GameObject)
	{
		Engine::Safe_Release(pInstance);
	}
	m_pList_GameObject.clear();
}
