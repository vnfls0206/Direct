#include "stdafx.h"
#include "CComponent_Manager.h"

IMPLEMENT_SINGLETON(Engine::CComponent_Manager)

Engine::CComponent * Engine::CComponent_Manager::Check_Component_Overlapped_InMap(const TCHAR * pKey)
{
	if (pKey == nullptr) {
		MSG_BOX("중복체크 시 비교할 키값이 잘못되었습니다!")
		return nullptr;
	}
	
	auto iter_find = find_if(map_Proto_Component.begin(), map_Proto_Component.end(), CFinder_Tag(pKey));
	if(iter_find == map_Proto_Component.end()){
		return nullptr;
	}
	return iter_find->second;
}
HRESULT Engine::CComponent_Manager::Add_Component_In_Map(const TCHAR * pKey, CComponent * pComponent)
{
	if (pComponent == nullptr)
	{
		MSG_BOX("들어온 컴포넌트가 NULLPTR 입니다!");
		return E_FAIL;
	}
	
	Engine::CComponent* tmp_pComponent = Check_Component_Overlapped_InMap(pKey);
	if (tmp_pComponent != nullptr) {
		MSG_BOX("중복된 컴포넌트가 존재합니다!");
		return E_FAIL;
	}

	map_Proto_Component.emplace(pKey, pComponent);

	return S_OK;
}

Engine::CComponent * Engine::CComponent_Manager::Get_Component_In_Map_By_Clone(const TCHAR * pKey)
{
	Engine::CComponent* pComponent = Check_Component_Overlapped_InMap(pKey);
	if (pComponent == nullptr) {
		MSG_BOX("게임오브젝트로 넘겨줄 컴포넌트를 찾을 수 없었습니다! [Clone]");
		return nullptr;
	}

	pComponent = pComponent->Clone();
	if (pComponent == nullptr) {
		MSG_BOX("컴포넌트 복제에 실패해, 컴포넌트 매니저에서, 객체를 복사받지 못했습니다!");
		return nullptr;
	}

	return pComponent;
}

Engine::CComponent * Engine::CComponent_Manager::Get_Component_In_Map_By_Proto(const TCHAR * pKey)
{
	Engine::CComponent* pComponent = Check_Component_Overlapped_InMap(pKey);
	if (pComponent == nullptr) {
		MSG_BOX("게임오브젝트로 넘겨줄 컴포넌트를 찾을 수 없었습니다! [Proto]");
		return nullptr;
	}
	return pComponent;
}

void Engine::CComponent_Manager::Free()
{
	for (auto& pPair : map_Proto_Component)
	{
		Engine::Safe_Release(pPair.second);
	}
	map_Proto_Component.clear();
}
