#ifndef CBuffer_h__
#define CBuffer_h__

#include "CComponent.h"

// VI : Vertex, Index

BEGIN(Engine)

class ENGINE_DLL CBuffer abstract
	: public Engine::CComponent
{
protected :
	explicit CBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBuffer(const CBuffer& rhs);
	virtual ~CBuffer() = default;


public  :
	HRESULT Make_Buffer();
	HRESULT Draw_Buffer();

protected :
	LPDIRECT3DVERTEXBUFFER9			m_pVertexBuffer;
	unsigned int					m_iVertexSize = 0;		// 정점 구조체, 그 크기를 의미.
	unsigned int					m_iNumVertices = 0;		// 정점의 개수
	unsigned long					m_dwVtxFVF = 0;			// 정점 유연정보

	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;
	unsigned int					m_iIndexSize = 0;
	unsigned int					m_iNumSubSets = 0;
	D3DFORMAT						m_IndexFmt;

public :
	virtual CComponent* Clone() = 0;

public  :
	virtual void Free();
};

END

#endif