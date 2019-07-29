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
	HRESULT Insert_Timer(const TCHAR* pName);					// �ʺ����� Ÿ�̸Ӹ� �ֽ��ϴ�!
	float	Update_Timer(const TCHAR* pName);					// �ʺ������� Ÿ�̸Ӹ� ã�� �����ŵ�ϴ�.


	CTimer* Get_Timer_Info(const TCHAR* pName);

	// CBase��(��) ���� ��ӵ�
public :
	virtual void Free() override;
};

END
#endif