#include "stdafx.h"
#include "CTexture.h"

USING(Engine)

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device),
	m_iMaxTextureIndex(0),				// 첫 텍스처의 인덱스를 의미하고
	m_iMinTextureIndex(0)				// 마지막 텍스처의 인덱스를 의미한다.
{
}

CTexture::CTexture(const CTexture & rhs)
	:CComponent(rhs),
	m_iMaxTextureIndex(rhs.m_iMaxTextureIndex),
	m_iMinTextureIndex(rhs.m_iMinTextureIndex),
	m_vecTextureArray(rhs.m_vecTextureArray)
{
}

HRESULT CTexture::Add_Texture_Array_To_Vector(const TCHAR * pTexPath, const TCHAR* pTexExtension,
	const int iTextureMinIndex, const int iTextureMaxIndex)
{
	if (pTexPath == nullptr){
		return E_FAIL;
	}
	else if (iTextureMinIndex > iTextureMaxIndex) {
		return E_FAIL;
	}
	else if (!lstrcmp(pTexPath, L"")) {
		return E_FAIL;
	}

	if (pTexExtension == nullptr) {
		return E_FAIL;
	}
	else if (!lstrcmp(pTexExtension, L"")) {
		return E_FAIL;
	}

	m_iMaxTextureIndex = iTextureMaxIndex;
	m_iMinTextureIndex = iTextureMinIndex;

	TCHAR tMaxPath[MAX_PATH], tTexNum[10], tExtension[15];
	ZeroMemory(&tMaxPath, sizeof(tMaxPath));	
	ZeroMemory(&tTexNum, sizeof(tTexNum));
	ZeroMemory(&tExtension, sizeof(tExtension));

	lstrcpy(tExtension, pTexExtension);

	for (int i = m_iMinTextureIndex; i <= m_iMaxTextureIndex; i++) {
		ZeroMemory(&tMaxPath, sizeof(tMaxPath));
		
		lstrcat(tMaxPath, pTexPath);		// 현재까지 받아온 경로를 넣습니다!
		
		swprintf_s(tTexNum, L"%d", i);		// 텍스처 명(숫자)를 문자열로 변환
		lstrcat(tMaxPath, tTexNum);			// 경로 + 숫자(텍스처명)

		lstrcat(tMaxPath, tExtension);		// 경로 + 숫자 + 확장자명 까지 총 경로를 세팅

		LPDIRECT3DTEXTURE9 pTexture;

		//D3DXCreateTextureFromFile(Get_Graphic_Device(), tMaxPath, &pTexture);
		D3DXCreateTextureFromFileEx(Get_Graphic_Device(), tMaxPath, 0, 0, 0, 0,
			D3DFMT_A8P8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(255,147, 187, 236), NULL, NULL, &pTexture);

		
	

		m_vecTextureArray.push_back(pTexture);
	}

	return NOERROR;
}

LPDIRECT3DTEXTURE9 CTexture::Get_Texture_From_Array_In_Vector(const int & iIndex)
{
	// 벡터를 기준으로, 우리가 선택한 인덱스의 텍스처를 뽑아오는 기능
	if (iIndex > m_iMaxTextureIndex)
		return nullptr;
	else if (iIndex < m_iMinTextureIndex)
		return nullptr;




	return m_vecTextureArray[iIndex];
}

CComponent * CTexture::Create(LPDIRECT3DDEVICE9 pGraphic_Device,
	const TCHAR* pTexPath, const TCHAR* pTexExtension,
	const int iTextureMinIndex, const int iTextureMaxIndex)
{
	CTexture* pInstance = new CTexture(pGraphic_Device);
	if (FAILED(pInstance->Add_Texture_Array_To_Vector
	(pTexPath, pTexExtension, iTextureMinIndex, iTextureMaxIndex)))
	{
		MSG_BOX("텍스처 초기화 오류");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CTexture::Clone()
{
	return  new CTexture(*this);
}

void CTexture::Free()
{
	for (auto& pInstance : m_vecTextureArray)
		Engine::Safe_Release(pInstance);
	m_vecTextureArray.clear();					// 사이즈 정리
	m_vecTextureArray.shrink_to_fit();			// 캐퍼시티 정리
}
