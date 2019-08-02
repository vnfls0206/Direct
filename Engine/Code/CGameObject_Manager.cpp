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
		// 생성하지 않았을 떄, 공간을 예약.
		// 생성되있는 상태라면?

		m_mapProto = new MAPPROTO[iNumScene];
		m_mapLayer = new MAPLAYER[iNumScene];
		// new...? => 메모리 누수(leak) => 못 찾아 => 그 주소를 가리키는 포인터가 초기화, 못찾아...반드시 릭 발생, 컴퓨터를 껐다켜야함.		
	}
}

void Engine::CGameObject_Manager::Insert_Prototype_GameObject_To_ProtoMap(int iSceneID,  
	const TCHAR * pProtoTag, Engine::CGameObject * pGameObject)
{
	if (pGameObject == nullptr) {
		MSG_BOX("NULLPTR 인 게임오브젝트가 프로토타입 맵 변수 안에 접근했습니다!");
		return;
	}
	if (Find_GameObejct_In_ProtoMap(iSceneID, pProtoTag) != nullptr) {
		MSG_BOX("중복된 프로토타입 오브젝트가 있습니다! [오브젝트매니저]");
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
	// 위 구문은, 프로토타입 맵에서, 내가 찾고 싶은 객체를 찾아오는 역할을 합니다!
	if (pProtoGameObject == nullptr)
	{
		MSG_BOX("해당 게임오브젝트가 프로토타입 맵에서 발견되지 않았습니다!");
		return nullptr;
	}

	Engine::CGameObject* pCloneObject = pProtoGameObject->Clone();
	if (pCloneObject == nullptr)
	{
		MSG_BOX("프로토타입 객체에서 제대로 복사되지 않았습니다!");
		Engine::Safe_Release(pCloneObject);
		return pCloneObject;
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
