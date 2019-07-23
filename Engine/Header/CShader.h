#ifndef CShader_h__
#define CShader_h__

#include "CComponent.h"

BEGIN(Engine)
class ENGINE_DLL CShader final
	: public Engine::CComponent
{
private :
	explicit CShader(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CShader(const CShader& rhs);
	virtual ~CShader() = default;

private :
	HRESULT	Add_Shader_FromFile(const TCHAR* pShaderPath);
	HRESULT Add_Shader_FromProto();


private :
	TCHAR					m_tFilePath[MAX_PATH];

private :
	LPD3DXEFFECT			m_pEffectShader;
public :
	LPD3DXEFFECT			Get_Effect() { return m_pEffectShader; }

	// 로컬스페이스 행렬
public:
	void					Set_Object_Matrix(const CHAR* pConstantKey, const D3DXMATRIX* pMatrix);

	// 텍스처
public:
	void						Set_Object_Texture(const CHAR* pConstantKey, const LPDIRECT3DTEXTURE9 pTexture);


public :
	static CComponent* Create(LPDIRECT3DDEVICE9 pGraphic_Device, const TCHAR* pShaderPath);
	virtual CComponent* Clone() override;
	virtual void Free() override;
};

END
#endif