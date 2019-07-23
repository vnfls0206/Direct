#include "stdafx.h"
#include "CTimer.h"


Engine::CTimer::CTimer()
	: m_fTimedelta(0.f)
{
}

HRESULT Engine::CTimer::Init_Timer()
{
	QueryPerformanceCounter(&m_fFrametime);			// 이 함수는, 현재(선언했을때, 이함수를!)의 클럭수를 받아옵니다!
	QueryPerformanceCounter(&m_fLasttime);
	QueryPerformanceCounter(&m_fFixTime);
	QueryPerformanceFrequency(&m_fCpuTick);			// 이 함수는, 1초당 총 클럭수를 받아옵니다!!!

	if (m_fFrametime.QuadPart == 0 || m_fLasttime.QuadPart == 0 || m_fFixTime.QuadPart == 0 || m_fCpuTick.QuadPart == 0) {
		return E_FAIL;
	}
	return NOERROR;
}
float Engine::CTimer::Calculate_Timer()
{
	QueryPerformanceCounter(&m_fFrametime);					// 끝지점
	if ((m_fFrametime.QuadPart - m_fFixTime.QuadPart) >= m_fCpuTick.QuadPart)
	{
		// 초당 한번씩
		QueryPerformanceFrequency(&m_fCpuTick);
		m_fFixTime = m_fFrametime;
	}

	m_fTimedelta = (((m_fFrametime.QuadPart - m_fLasttime.QuadPart)) / (float)m_fCpuTick.QuadPart);
	//																	1초에 한번씩 계산되는, 초당 진동수
	m_fLasttime = m_fFrametime;
	return m_fTimedelta;
}


Engine::CTimer * Engine::CTimer::Create()
{
	CTimer* pInstance = new CTimer;
	if (FAILED(pInstance->Init_Timer()))
	{
		MSG_BOX("타이머 초기화에 실패했습니다!");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
void Engine::CTimer::Free()
{
}
