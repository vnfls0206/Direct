#ifndef CFont_h__
#define CFont_h__

#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CFont final :
	public Engine::CBase
{
private :
	explicit CFont();
	virtual ~CFont() = default;


private :
	HRESULT Initialize_Font(LPDIRECT3DDEVICE9 pGraphicDev, int iHeight, unsigned int uiWidth, unsigned int uiWeight, const TCHAR* pFaceName);
public :
	void Render_Font(const TCHAR* pSentence, POINT SenPoint, D3DCOLOR pARGB);


private :
	LPDIRECT3DDEVICE9 m_pDevice;
	D3DXFONT_DESC	m_tagFontDesc;
	LPD3DXFONT		m_pFont;

public :
	static CFont* Create(LPDIRECT3DDEVICE9 pGraphicDev, int iHeight, unsigned int uiWidth, unsigned int uiWeight, const TCHAR* pFaceName);
	virtual void Free() override;

};

END
#endif