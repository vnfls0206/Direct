#ifndef CTimerMgr_h__
#define CTimerMgr_h__

#include "CBase.h"

BEGIN(Engine)

class CTimer;
class ENGINE_DLL CTimerMgr
	: public CBase
{
	DECLARE_SINGLETON(CTimerMgr)

private :
	explicit CTimerMgr() = default;
	virtual ~CTimerMgr() = default;

private :
	typedef map<const TCHAR*, CTimer*>		MAPTIMER;
	MAPTIMER								map_Timer;

public :
	HRESULT Insert_Timer(const TCHAR* pName);					// 맵변수에 타이머를 넣습니다!
	float	Update_Timer(const TCHAR* pName);					// 맵변수에서 타이머를 찾아 실행시킵니다.


	CTimer* Get_Timer_Info(const TCHAR* pName);

	// CBase을(를) 통해 상속됨
public :
	virtual void Free() override;
};

END
#endif