#ifndef CComponent_h__
#define CComponent_h__

#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CComponent abstract 
	: public Engine::CBase
{
protected :
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphic_Device);	// 持失切
	explicit CComponent(const CComponent& rhs);					// 差紫持失切
	virtual ~CComponent() = default;

private :
	LPDIRECT3DDEVICE9		m_pGraphic_Device = nullptr;
protected :
	LPDIRECT3DDEVICE9		Get_Graphic_Device();


public :
	virtual CComponent* Clone() = 0;

public :
	virtual void Free() override;
};

END
#endif