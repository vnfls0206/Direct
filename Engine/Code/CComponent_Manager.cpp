#include "stdafx.h"
#include "CComponent_Manager.h"

IMPLEMENT_SINGLETON(Engine::CComponent_Manager)

Engine::CComponent * Engine::CComponent_Manager::Check_Component_Overlapped_InMap(const TCHAR * pKey)
{
	if (pKey == nullptr) {
		MSG_BOX("�ߺ�üũ �� ���� Ű���� �߸��Ǿ����ϴ�!")
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
		MSG_BOX("���� ������Ʈ�� NULLPTR �Դϴ�!");
		return E_FAIL;
	}
	
	Engine::CComponent* tmp_pComponent = Check_Component_Overlapped_InMap(pKey);
	if (tmp_pComponent != nullptr) {
		MSG_BOX("�ߺ��� ������Ʈ�� �����մϴ�!");
		return E_FAIL;
	}

	map_Proto_Component.emplace(pKey, pComponent);

	return S_OK;
}

Engine::CComponent * Engine::CComponent_Manager::Get_Component_In_Map_By_Clone(const TCHAR * pKey)
{
	Engine::CComponent* pComponent = Check_Component_Overlapped_InMap(pKey);
	if (pComponent == nullptr) {
		MSG_BOX("���ӿ�����Ʈ�� �Ѱ��� ������Ʈ�� ã�� �� �������ϴ�! [Clone]");
		return nullptr;
	}

	pComponent = pComponent->Clone();
	if (pComponent == nullptr) {
		MSG_BOX("������Ʈ ������ ������, ������Ʈ �Ŵ�������, ��ü�� ������� ���߽��ϴ�!");
		return nullptr;
	}

	return pComponent;
}

Engine::CComponent * Engine::CComponent_Manager::Get_Component_In_Map_By_Proto(const TCHAR * pKey)
{
	Engine::CComponent* pComponent = Check_Component_Overlapped_InMap(pKey);
	if (pComponent == nullptr) {
		MSG_BOX("���ӿ�����Ʈ�� �Ѱ��� ������Ʈ�� ã�� �� �������ϴ�! [Proto]");
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
