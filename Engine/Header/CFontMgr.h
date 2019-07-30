#ifndef CFontMgr_h__
#define CFontMgr_h__

#include "CBase.h"
BEGIN(Engine)

class CFont;
class ENGINE_DLL CFontMgr final :
	public Engine::CBase
{
		DECLARE_SINGLETON(CFontMgr)
private :
	explicit CFontMgr() = default;
	virtual ~CFontMgr() = default;

public :
	// 폰트 생성
	HRESULT Add_Font(LPDIRECT3DDEVICE9 pGraphicDev, int iHeight, unsigned int uiWidth, unsigned int uiWeight, const TCHAR* pFaceName);
	// 폰트 출력
	void Render_Font(const TCHAR * pFontKey, const TCHAR* pSentence, POINT SenPoint, D3DCOLOR pARGB);

private :
	// 중복 폰트 점검
	CFont* Check_Overlapped_Fonts(const TCHAR* pFontKey);

private :
	typedef map<const TCHAR*, CFont*>				MAPFONT;
	MAPFONT									m_MapFont;

public :
	virtual void Free() override;
};

END
#endif