#include "stdafx.h"
#include "CFont.h"

USING(Engine)

CFont::CFont()
	: m_pFont(nullptr),
		m_pDevice()
{

}

HRESULT CFont::Initialize_Font(LPDIRECT3DDEVICE9 pGraphicDev, int iHeight, unsigned int uiWidth, unsigned int uiWeight, const TCHAR * pFaceName)
{
	ZeroMemory(&m_tagFontDesc, sizeof(D3DXFONT_DESC));
	m_tagFontDesc.CharSet = HANGUL_CHARSET;
	lstrcpy(m_tagFontDesc.FaceName, pFaceName);
	m_tagFontDesc.Height = iHeight;
	m_tagFontDesc.Width = uiWidth;
	m_tagFontDesc.Weight = uiWeight;

	D3DXCreateFontIndirect(pGraphicDev,&m_tagFontDesc, &m_pFont);

	return NOERROR;
}

void CFont::Render_Font(const TCHAR* pSentence, POINT SenPoint, D3DCOLOR pARGB)
{
	RECT rc = {
		SenPoint.x,
		SenPoint.y,
		SenPoint.x + m_tagFontDesc.Width,
		SenPoint.y - m_tagFontDesc.Height
	};

	if (m_pFont != nullptr)
		m_pFont->DrawTextW(NULL, pSentence,lstrlen(pSentence), &rc, DT_NOCLIP, pARGB);
}

CFont * CFont::Create(LPDIRECT3DDEVICE9 pGraphicDev, int iHeight, unsigned int uiWidth, unsigned int uiWeight, const TCHAR * pFaceName)
{
	CFont* pInstance = new CFont();
	if (FAILED(pInstance->Initialize_Font(pGraphicDev, iHeight, uiWidth, uiWeight, pFaceName)))
	{
		MSG_BOX("폰트 생성에 실패했습니다!");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

void CFont::Free()
{
	Engine::Safe_Release(m_pFont);
}

