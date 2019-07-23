#ifndef CBuffer_RcTex_h__
#define CBuffer_RcTex_h__

#include "CBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CBuffer_RcTex
	: public Engine::CBuffer
{
private :
	explicit CBuffer_RcTex(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBuffer_RcTex(const CBuffer_RcTex& rhs);
	virtual ~CBuffer_RcTex() = default;

public :
	HRESULT Create_Buffer_RcTex();
private :
	HRESULT Initialize_CBuffer_RcTex();


public :
	static CBuffer_RcTex* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone() override;
	virtual void Free() override;
};

END
#endif