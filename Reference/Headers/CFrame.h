#ifndef CFrame_h__
#define CFrame_h__

#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CFrame final :
	public Engine::CBase
{
// m_fTimedelta => ��Ŭ�� Ÿ���� �����´�.
// �� ��Ŭ�� Ÿ����, �� 1/60 ���� �Ѵ´ٸ�? -> ����Ȥ�� ������Ʈ�� ��Ų��!!!!
// �׷�, ���� �� ������ �ǹ��ϴ� �ٴ�?
private :
	explicit CFrame();
	virtual ~CFrame() = default;

private :
	float	m_fTimeAcc = 0.f;			// m_fTimeDetla ���� ����
	float	m_fTimeInterval = 0.f;		// ���� �޾ƿ� ������ ���� ����

public :
	static CFrame* Create(const float fTimeItv);
	bool Update_Frame(const float& fTimeDelta);
private :
	HRESULT Init_Frame(const float fTimeItv);
public :
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END

#endif