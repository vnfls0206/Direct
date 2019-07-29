#include "stdafx.h"
#include "CTimer.h"


Engine::CTimer::CTimer()
	: m_fTimedelta(0.f)
{
}

HRESULT Engine::CTimer::Init_Timer()
{
	QueryPerformanceCounter(&m_fFrametime);			// �� �Լ���, ����(����������, ���Լ���!)�� Ŭ������ �޾ƿɴϴ�!
	QueryPerformanceCounter(&m_fLasttime);
	QueryPerformanceCounter(&m_fFixTime);
	QueryPerformanceFrequency(&m_fCpuTick);			// �� �Լ���, 1�ʴ� �� Ŭ������ �޾ƿɴϴ�!!!

	if (m_fFrametime.QuadPart == 0 || m_fLasttime.QuadPart == 0 || m_fFixTime.QuadPart == 0 || m_fCpuTick.QuadPart == 0) {
		return E_FAIL;
	}
	return NOERROR;
}
float Engine::CTimer::Calculate_Timer()
{
	QueryPerformanceCounter(&m_fFrametime);					// ������
	if ((m_fFrametime.QuadPart - m_fFixTime.QuadPart) >= m_fCpuTick.QuadPart)
	{
		// �ʴ� �ѹ���
		QueryPerformanceFrequency(&m_fCpuTick);
		m_fFixTime = m_fFrametime;
	}

	m_fTimedelta = ((m_fFrametime.QuadPart - m_fLasttime.QuadPart)/ (float)m_fCpuTick.QuadPart);
	//																	1�ʿ� �ѹ��� ���Ǵ�, �ʴ� ������
	m_fTimedelta *= m_fBulletTime;
	m_fLasttime = m_fFrametime;
	return m_fTimedelta;
}

void Engine::CTimer::Set_BulletTime(float fValue)
{
	if (fValue <= 0.f)
	{
		m_fBulletTime = 1.f;
	}
	else if (fValue > 0.f)
	{
		m_fBulletTime = fValue;
	}
}


Engine::CTimer * Engine::CTimer::Create()
{
	CTimer* pInstance = new CTimer;
	if (FAILED(pInstance->Init_Timer()))
	{
		MSG_BOX("Ÿ�̸� �ʱ�ȭ�� �����߽��ϴ�!");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
void Engine::CTimer::Free()
{
}
