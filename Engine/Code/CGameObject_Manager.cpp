#include "stdafx.h"
#include "CGameObject_Manager.h"

IMPLEMENT_SINGLETON(Engine::CGameObject_Manager)


Engine::CGameObject_Manager::CGameObject_Manager()
	: m_mapProto(nullptr)
	, m_mapLayer(nullptr)
{
}

void Engine::CGameObject_Manager::Reserve_Proto_Layer_Array(const int iNumScene)
{
	m_iSceneNum = iNumScene;

	m_mapProto = nullptr;
	m_mapLayer = nullptr;

	if (m_mapProto == nullptr || m_mapLayer == nullptr) {
		// �������� �ʾ��� ��, ������ ����.
		// �������ִ� ���¶��?

		m_mapProto = new MAPPROTO[iNumScene];
		m_mapLayer = new MAPLAYER[iNumScene];
		// new...? => �޸� ����(leak) => �� ã�� => �� �ּҸ� ����Ű�� �����Ͱ� �ʱ�ȭ, ��ã��...�ݵ�� �� �߻�, ��ǻ�͸� �����Ѿ���.		
	}
}

void Engine::CGameObject_Manager::Insert_Prototype_GameObject_To_ProtoMap(int iSceneID,  
	const TCHAR * pProtoTag, Engine::CGameObject * pGameObject)
{
	if (pGameObject == nullptr) {
		MSG_BOX("NULLPTR �� ���ӿ�����Ʈ�� ������Ÿ�� �� ���� �ȿ� �����߽��ϴ�!");
		return;
	}
	if (Find_GameObejct_In_ProtoMap(iSceneID, pProtoTag) != nullptr) {
		MSG_BOX("�ߺ��� ������Ÿ�� ������Ʈ�� �ֽ��ϴ�! [������Ʈ�Ŵ���]");
		return;
	}
	m_mapProto[iSceneID].emplace(pProtoTag, pGameObject);
}
Engine::CGameObject* Engine::CGameObject_Manager::Find_GameObejct_In_ProtoMap(int iSceneID,  const TCHAR * pProtoTag)
{
	auto iter_find = find_if(m_mapProto[iSceneID].begin(), m_mapProto[iSceneID].end(), 
		CFinder_Tag(pProtoTag));

	if (iter_find == m_mapProto[iSceneID].end())
		return nullptr;

	return iter_find->second;
}
void Engine::CGameObject_Manager::Release_Map_All_Object(int iSceneID)
{
	for (auto& pInstance : m_mapLayer[iSceneID]) {
		Engine::Safe_Release(pInstance.second);
	}
	m_mapLayer[iSceneID].clear();


	for (auto& pInstance : m_mapProto[iSceneID]){
		Engine::Safe_Release(pInstance.second);
	}
	m_mapProto[iSceneID].clear();
}
void Engine::CGameObject_Manager::Update_Layers(int iSceneID, const float & fTimeDelta)
{
	if (m_mapLayer[iSceneID].empty()) {
		return;
	}

	for (auto& pInstance : m_mapLayer[iSceneID]) {
		pInstance.second->Update_Layer(fTimeDelta);
	}
}

Engine::CGameObject* Engine::CGameObject_Manager::Copy_Proto_GameObject_To_Layer(int iProtoSceneID,
	const TCHAR * pProtoObjectTag, int iLayerSceneID,  const TCHAR * pLayerObjectTag)
{
	Engine::CGameObject* pProtoGameObject = Find_GameObejct_In_ProtoMap(iProtoSceneID, pProtoObjectTag);
	// �� ������, ������Ÿ�� �ʿ���, ���� ã�� ���� ��ü�� ã�ƿ��� ������ �մϴ�!
	if (pProtoGameObject == nullptr)
	{
		MSG_BOX("�ش� ���ӿ�����Ʈ�� ������Ÿ�� �ʿ��� �߰ߵ��� �ʾҽ��ϴ�!");
		return nullptr;
	}

	Engine::CGameObject* pCloneObject = pProtoGameObject->Clone();
	if (pCloneObject == nullptr)
	{
		MSG_BOX("������Ÿ�� ��ü���� ����� ������� �ʾҽ��ϴ�!");
		Engine::Safe_Release(pCloneObject);
		return nullptr;
	}

	Engine::CLayer* pLayer = Find_Layer(iLayerSceneID, pLayerObjectTag);
	if (pLayer == nullptr) {
		// ??
		pLayer = CLayer::Create();
		pLayer->Insert_GameObject_To_Layer(pCloneObject);
		m_mapLayer[iLayerSceneID].emplace(pLayerObjectTag, pLayer);
	}
	else if (pLayer != nullptr) {
		pLayer->Insert_GameObject_To_Layer(pCloneObject);
	}

	pCloneObject->Tag = pLayerObjectTag;

	return pCloneObject;
}

Engine::CLayer * Engine::CGameObject_Manager::Find_Layer(int iLayerSceneID, const TCHAR * pLayerObjectTag)
{
	auto iter_find = find_if(m_mapLayer[iLayerSceneID].begin(), m_mapLayer[iLayerSceneID].end(),
		CFinder_Tag(pLayerObjectTag));

	if (iter_find == m_mapLayer[iLayerSceneID].end())
		return nullptr;

	return iter_find->second;
}



void Engine::CGameObject_Manager::Free(){
	for (int i = 0; i < m_iSceneNum; i++)
	{
		for (auto& pInstance : m_mapProto[i])
			Engine::Safe_Release(pInstance.second);

		for (auto& pInstance : m_mapLayer[i])
			Engine::Safe_Release(pInstance.second);

	}
}
