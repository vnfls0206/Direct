#ifndef CTimer_h__
#define CTimer_h__

#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CTimer
	: public Engine::CBase
{
private :
	explicit CTimer();
	virtual ~CTimer() = default;


private :
	LARGE_INTEGER  m_fFrametime;		// Counter: ���� Ŭ������ �޾ƿ��¿���
	LARGE_INTEGER  m_fLasttime;
	LARGE_INTEGER  m_fFixTime;
	LARGE_INTEGER  m_fCpuTick;			// Frequency : 1�ʴ� Ŭ������ ������ �޾ƿ��� ������ ��.

private :
	float m_fTimedelta = 0.f;


private :
	HRESULT Init_Timer();
public :
	float Calculate_Timer();


public:
	static CTimer* Create();
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END

#endif