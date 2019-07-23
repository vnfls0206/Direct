#ifndef CTexture_h__
#define CTexture_h__

#include "CComponent.h"

BEGIN(Engine)
class ENGINE_DLL CTexture final
	: public Engine::CComponent
{
private :
	explicit CTexture(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CTexture(const CTexture& rhs);
	virtual ~CTexture() = default;

private :
	// 삽입
	HRESULT								Add_Texture_Array_To_Vector(
		const TCHAR* pTexPath, const TCHAR* pTexExtension,
		const int iTextureMinIndex, const int iTextureMaxIndex);
public :
	// 특정 인덱스의 텍스처를 가져오는 함수
	LPDIRECT3DTEXTURE9					Get_Texture_From_Array_In_Vector(const int& iIndex);

private :
	int									m_iMaxTextureIndex;
	int									m_iMinTextureIndex;

private :
	vector<LPDIRECT3DTEXTURE9>			m_vecTextureArray;

public :
	static CComponent* Create(LPDIRECT3DDEVICE9 pGraphic_Device,
		const TCHAR* pTexPath, const TCHAR* pTexExtension,
		const int iTextureMinIndex, const int iTextureMaxIndex);
	virtual CComponent* Clone() override;
	virtual void Free() override;

};

END
#endif
