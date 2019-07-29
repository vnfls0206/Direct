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
	LARGE_INTEGER  m_fFrametime;		// Counter: 현재 클럭수를 받아오는역할
	LARGE_INTEGER  m_fLasttime;
	LARGE_INTEGER  m_fFixTime;
	LARGE_INTEGER  m_fCpuTick;			// Frequency : 1초당 클럭수의 총합을 받아오는 역할을 함.

private :
	float m_fTimedelta = 0.f;
	float m_fBulletTime = 1.f;			//Timedelta에 곱하는 값

private :
	HRESULT Init_Timer();
public :
	float Calculate_Timer();
	void Set_BulletTime(float fValue);	//fValue값이 0이되면 안되며 1보다 크면 빨라지고 1보다 작으면 느려진다


public:
	static CTimer* Create();
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};

END

#endif