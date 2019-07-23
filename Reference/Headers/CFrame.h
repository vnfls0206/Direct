#ifndef CFrame_h__
#define CFrame_h__

#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CFrame final :
	public Engine::CBase
{
// m_fTimedelta => 한클럭 타임을 가져온다.
// 이 한클럭 타임이, 저 1/60 값을 넘는다면? -> 렌더혹은 업데이트를 시킨다!!!!
// 그럼, 위의 두 문장이 의미하는 바는?
private :
	explicit CFrame();
	virtual ~CFrame() = default;

private :
	float	m_fTimeAcc = 0.f;			// m_fTimeDetla 값의 누적
	float	m_fTimeInterval = 0.f;		// 내가 받아올 프레임 값을 저장

public :
	static CFrame* Create(const float fTimeItv);
	bool Update_Frame(const float& fTimeDelta);
private :
	HRESULT Init_Frame(const float fTimeItv);
public :
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};

END

#endif