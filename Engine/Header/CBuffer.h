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
	unsigned int					m_iVertexSize = 0;		// ���� ����ü, �� ũ�⸦ �ǹ�.
	unsigned int					m_iNumVertices = 0;		// ������ ����
	unsigned long					m_dwVtxFVF = 0;			// ���� ��������

	LPDIRECT3DINDEXBUFFER9			m_pIndexBuffer;
	unsigned int					m_iIndexSize = 0;
	unsigned int					m_iNumSubSets = 0;
	D3DFORMAT						m_IndexFmt;

public:
	UINT Get_NumVertices();
	ULONG Get_FVF();

public :
	virtual CComponent* Clone() = 0;

public  :
	virtual void Free();
};

END

#endif