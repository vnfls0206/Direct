#ifndef CFrameMgr_h__
#define CFrameMgr_h__

#include "CBase.h"

BEGIN(Engine)

class CFrame;
class ENGINE_DLL CFrameMgr final
	: public CBase
{
DECLARE_SINGLETON(CFrameMgr)

private :
	explicit CFrameMgr() = default;
	virtual ~CFrameMgr() = default;

public :
	HRESULT Insert_Frame(const TCHAR* pChar, CFrame* pFrame);
	bool Update_Frame(const TCHAR* pChar, const float& fTimeDelta);
private :
	Engine::CFrame* Get_Frame_Info(const TCHAR* pChar);

private :
	typedef map<const TCHAR*, CFrame*>			MAPFRAME;
	MAPFRAME									mapFrame;

// CBase��(��) ���� ��ӵ�
public :
	virtual void Free() override;
};

END

#endif