#include "stdafx.h"
#include "CFontMgr.h"
#include "CFont.h"

IMPLEMENT_SINGLETON(Engine::CFontMgr)

HRESULT Engine::CFontMgr::Add_Font(LPDIRECT3DDEVICE9 pGraphicDev, int iHeight, unsigned int uiWidth, unsigned int uiWeight, const TCHAR * pFaceName)
{
	if (Check_Overlapped_Fonts(pFaceName) == nullptr)
	{// ������ ������ �մϴ�.
		Engine::CFont* pFont = CFont::Create(pGraphicDev, iHeight, uiWidth, uiWeight, pFaceName);
		m_MapFont.emplace(pFaceName, pFont);
	}
	else{
		MSG_BOX("���� ��Ʈ�� �ι� �����߽��ϴ�.");
		return E_FAIL;
	}
	return NOERROR;
}

void Engine::CFontMgr::Render_Font(const TCHAR * pFontKey, const TCHAR * pSentence, POINT SenPoint, D3DCOLOR pARGB)
{
	Engine::CFont* pFont = Check_Overlapped_Fonts(pFontKey);
	if (pFont == nullptr)
	{
		MSG_BOX("�ش� ��Ʈ�� �������� �ʽ��ϴ�..");
		return;
	}

	pFont->Render_Font(pSentence, SenPoint, pARGB);
}

Engine::CFont * Engine::CFontMgr::Check_Overlapped_Fonts(const TCHAR * pFontKey){
	auto iter_find = find_if(m_MapFont.begin(), m_MapFont.end(), CFinder_Tag(pFontKey));
	if (iter_find == m_MapFont.end()) {
		// ��ã�Ҿ��.
		return nullptr;
	}
	return iter_find->second;
}

void Engine::CFontMgr::Free()
{
	for (auto& pInstance : m_MapFont)
		Engine::Safe_Release(pInstance.second);
	m_MapFont.clear();
}
