#ifndef CComponent_Manager_h__
#define CComponent_Manager_h__


#include "CBase.h"
#include "CComponent.h"

BEGIN(Engine)

class ENGINE_DLL CComponent_Manager
	: public Engine::CBase
{
private :
	explicit CComponent_Manager() = default;
	virtual ~CComponent_Manager() = default;

DECLARE_SINGLETON(CComponent_Manager)

private :
	typedef map<const TCHAR*, CComponent*>		MAPPROTO;
	MAPPROTO									map_Proto_Component;

public :
	// �ߺ�üũ
	CComponent*								Check_Component_Overlapped_InMap(const TCHAR* pKey);		// Ű���� ���ؼ� �ߺ��� üũ�մϴ�!
	// ������ҿ� �ִ°�.
	HRESULT									Add_Component_In_Map(const TCHAR* pKey, CComponent* pComponent);
	// ������ҿ��� �����°�.
	CComponent*								Get_Component_In_Map_By_Clone(const TCHAR* pKey);
	CComponent*								Get_Component_In_Map_By_Proto(const TCHAR* pKey);

public :
	virtual void Free() override;
};

END

#endif