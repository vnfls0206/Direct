#include "stdafx.h"
#include "CBuffer.h"


Engine::CBuffer::CBuffer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}

Engine::CBuffer::CBuffer(const CBuffer & rhs)
	: CComponent(rhs)
	, m_pVertexBuffer(rhs.m_pVertexBuffer)
	, m_iVertexSize(rhs.m_iVertexSize)
	, m_iNumVertices(rhs.m_iNumVertices)
	, m_dwVtxFVF(rhs.m_dwVtxFVF)
	, m_iIndexSize(rhs.m_iIndexSize)
	, m_pIndexBuffer(rhs.m_pIndexBuffer)
	, m_iNumSubSets(rhs.m_iNumSubSets)
	, m_IndexFmt(rhs.m_IndexFmt)
{
}

HRESULT Engine::CBuffer::Make_Buffer()
{
	LPDIRECT3DDEVICE9 pGraphicDev = Get_Graphic_Device();
	if (nullptr == pGraphicDev)
		return E_FAIL;

	if (FAILED(pGraphicDev->CreateVertexBuffer(m_iVertexSize * m_iNumVertices,
		0, m_dwVtxFVF, D3DPOOL_MANAGED, &m_pVertexBuffer, 0)))
		return E_FAIL;

	if (FAILED(pGraphicDev->CreateIndexBuffer(m_iIndexSize * m_iNumSubSets, 0, 
		m_IndexFmt, D3DPOOL_MANAGED, &m_pIndexBuffer, 0)))
		return E_FAIL;

	return NOERROR;
}

HRESULT Engine::CBuffer::Draw_Buffer()
{
	Get_Graphic_Device()->SetStreamSource(0, m_pVertexBuffer, 0, m_iVertexSize);			// 정점 세팅하는 곳 
	Get_Graphic_Device()->SetFVF(m_dwVtxFVF);												// 정점 유연정보
	Get_Graphic_Device()->SetIndices(m_pIndexBuffer);										
	Get_Graphic_Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iNumVertices, 0, m_iNumSubSets);		
	// 정점들과, 인덱스 순서로 하여금 선으로 그어주는 역할....

	return NOERROR;
}

UINT Engine::CBuffer::Get_NumVertices()
{
	return m_iNumVertices;
}

ULONG Engine::CBuffer::Get_FVF()
{
	return m_dwVtxFVF;
}

void Engine::CBuffer::Free()
{
	CComponent::Free();

	Engine::Safe_Release(m_pVertexBuffer);
	Engine::Safe_Release(m_pIndexBuffer);
}


