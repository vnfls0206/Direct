#include "stdafx.h"
#include "CBuffer_RcTex.h"

USING(Engine)

CBuffer_RcTex::CBuffer_RcTex(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CBuffer(pGraphic_Device)
{
}
CBuffer_RcTex::CBuffer_RcTex(const CBuffer_RcTex & rhs)
	: CBuffer(rhs)
{
}

  
HRESULT CBuffer_RcTex::Create_Buffer_RcTex()
{
	m_iVertexSize = sizeof(VTXTEX);
	m_iNumVertices = 4;
	m_dwVtxFVF = D3DFVF_XYZ | D3DFVF_TEX1;

	m_iIndexSize = sizeof(POLYGON16);
	m_iNumSubSets = 2;
	m_IndexFmt = D3DFMT_INDEX16;

	if (FAILED(Make_Buffer()))
		return E_FAIL;		// 정점 버퍼를 생성을 했다!


	VTXTEX* pVertices = nullptr;
	POLYGON16* pIndexes = nullptr;

	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	
	pVertices[0].vPosition = D3DXVECTOR3(-0.5f, -0.5f, 0.f);
	pVertices[0].vTexUV = D3DXVECTOR2(1.0f, 1.0f);

	pVertices[1].vPosition = D3DXVECTOR3(0.5f, -0.5f, 0.f);
	pVertices[1].vTexUV = D3DXVECTOR2(0.0f, 1.0f);

	pVertices[2].vPosition = D3DXVECTOR3(0.5f, 0.5f, 0.f);
	pVertices[2].vTexUV = D3DXVECTOR2(0.0f, 0.0f);

	pVertices[3].vPosition = D3DXVECTOR3(-0.5f, 0.5f, 0.f);

	pVertices[3].vTexUV = D3DXVECTOR2(1.0f, 0.0f);
	
	/*pVertices[0].vPosition = D3DXVECTOR3(-0.5f, -0.5f, 0.f);
	pVertices[0].vTexUV = D3DXVECTOR2(1.0f, 1.0f);

	pVertices[1].vPosition = D3DXVECTOR3(0.5f, -0.5f, 0.f);
	pVertices[1].vTexUV = D3DXVECTOR2(0.0f, 1.0f);
=======
	pVertices[3].vTexUV = D3DXVECTOR2(1.0f, 0.0f);
>>>>>>> Stashed changes

	pVertices[2].vPosition = D3DXVECTOR3(0.5f, 0.5f, 0.f);
	pVertices[2].vTexUV = D3DXVECTOR2(0.0f, 0.0f);

	pVertices[3].vPosition = D3DXVECTOR3(-0.5f, 0.5f, 0.f);
	pVertices[3].vTexUV = D3DXVECTOR2(1.0f, 0.0f);*/
	m_pVertexBuffer->Unlock();
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndexes, 0);

	// 반시계방향으로 그릴거냐
	// 시계바향으로 그릴거냐? 
	pIndexes[0]._1 = 0;
	pIndexes[0]._2 = 1;
	pIndexes[0]._3 = 2;

	pIndexes[1]._1 = 0;
	pIndexes[1]._2 = 2;
	pIndexes[1]._3 = 3;

	m_pIndexBuffer->Unlock();

	return S_OK;
}

HRESULT CBuffer_RcTex::Initialize_CBuffer_RcTex()
{
	Create_Buffer_RcTex();
	return NOERROR;
}


CBuffer_RcTex * CBuffer_RcTex::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBuffer_RcTex* pInstance = new CBuffer_RcTex(pGraphic_Device);
	if (pInstance->Initialize_CBuffer_RcTex())
	{
		MSG_BOX("Error!");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
CComponent * CBuffer_RcTex::Clone()
{
	return new CBuffer_RcTex(*this);
}
void CBuffer_RcTex::Free()
{
	CBuffer::Free();
}

