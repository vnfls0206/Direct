#include "stdafx.h"
#include "CFrameMgr.h"
#include "CFrame.h"

IMPLEMENT_SINGLETON(Engine::CFrameMgr)

HRESULT Engine::CFrameMgr::Insert_Frame(const TCHAR * pChar, Engine::CFrame * pFrame)
{
	if (Get_Frame_Info(pChar) == nullptr) {
		if (pFrame == nullptr)
			MSG_BOX("Ű���� �ߺ��� ��������, ������ ��ü�� �� �����Դϴ�!");

		mapFrame.insert({ pChar, pFrame });
		return NOERROR;
	}
	else {
		MSG_BOX("������ Ű�� �ߺ�!!");
		return E_FAIL;
	}
}

bool Engine::CFrameMgr::Update_Frame(const TCHAR * pChar, const float& fTimeDelta)
{
	Engine::CFrame* pFrame = Get_Frame_Info(pChar);
	if (pFrame == nullptr) {
		MSG_BOX("������ ������ ��ü�� �������µ� �����߽��ϴ�!");
		return false;
	}
	return pFrame->Update_Frame(fTimeDelta);
}

Engine::CFrame * Engine::CFrameMgr::Get_Frame_Info(const TCHAR * pChar)
{
	auto iter_find = find_if(mapFrame.begin(), mapFrame.end(),
		[&](MAPFRAME::value_type pMapPair)->bool
	{
		return !lstrcmp(pMapPair.first, pChar);
	});

	if (iter_find == mapFrame.end()) {
		return nullptr;
	}

	return iter_find->second;
}

void Engine::CFrameMgr::Free()
{
	for (auto& pInstance : mapFrame)
		Engine::Safe_Release(pInstance.second);
	mapFrame.clear();
}
