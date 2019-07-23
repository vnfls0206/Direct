#include "stdafx.h"
#include "CTimerMgr.h"
#include "CTimer.h"

IMPLEMENT_SINGLETON(Engine::CTimerMgr)

HRESULT Engine::CTimerMgr::Insert_Timer(const TCHAR * pName)
{
	if (Get_Timer_Info(pName) == nullptr) {

		Engine::CTimer* pTimer = Engine::CTimer::Create();
		if (pTimer == nullptr) {
			MSG_BOX("타이머를 넣기위해, 생성하던 도중, 실패하였습니다!");
			return E_FAIL;
		}

		map_Timer.insert({ pName, pTimer });
		return NOERROR;
	}
	else {
		MSG_BOX("타이머 키값 중복!!");
		return E_FAIL;
	}
}

float Engine::CTimerMgr::Update_Timer(const TCHAR * pName)
{
	Engine::CTimer* pTimer = Get_Timer_Info(pName);
	if (pTimer == nullptr)
		return 0.f;
	else
		return pTimer->Calculate_Timer();
}

Engine::CTimer* Engine::CTimerMgr::Get_Timer_Info(const TCHAR * pName)
{
	auto iter_find = find_if(map_Timer.begin(), map_Timer.end(), 
		[&](MAPTIMER::value_type pMapPair)->bool
	{
		return !lstrcmp(pMapPair.first, pName);
	});

	if (iter_find == map_Timer.end()) {
		return nullptr;
	}

	return iter_find->second;
}

void Engine::CTimerMgr::Free()
{
	for (auto& pInstance : map_Timer){
		Engine::Safe_Release(pInstance.second);
	}
	map_Timer.clear();
}
