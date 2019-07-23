#include "stdafx.h"
#include "CFrame.h"


Engine::CFrame::CFrame()
	: m_fTimeAcc(0.f), m_fTimeInterval(0.f)
{	  
}

HRESULT Engine::CFrame::Init_Frame(const float fTimeItv)	// 60, 100, 30....Fps
{
	m_fTimeInterval = 1 / fTimeItv;

	return NOERROR;
}

Engine::CFrame * Engine::CFrame::Create(const float fTimeItv)
{
	CFrame* pFrame = new CFrame();
	if (FAILED(pFrame->Init_Frame(fTimeItv)))
	{
		MSG_BOX("프레임 생성 및 초기화 실패");
		Engine::Safe_Release(pFrame);
	}
	return pFrame;
}

bool Engine::CFrame::Update_Frame(const float & fTimeDelta)
{
	m_fTimeAcc += fTimeDelta;
	if (m_fTimeAcc >= m_fTimeInterval) 
	{
		m_fTimeAcc = 0.f;
		return true;		// 저는, 일정 순간에만 업데이트와 렌더링을 시킬겁니다!
	}
	return false;
}

void Engine::CFrame::Free()
{


}
