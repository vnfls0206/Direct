#include "stdafx.h"
#include "CShader.h"

USING(Engine)

CShader::CShader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{
}
CShader::CShader(const CShader & rhs)
	: CComponent(rhs)
{
	lstrcpy(m_tFilePath, rhs.m_tFilePath);
}




HRESULT CShader::Add_Shader_FromFile(const TCHAR* pShaderPath)
{
	if (pShaderPath == nullptr) {
		return E_FAIL;
	}
	else if (!lstrcmp(pShaderPath, L"")) {
		return E_FAIL;
	}
	lstrcpy(m_tFilePath, pShaderPath);

	return S_OK;
}

HRESULT CShader::Add_Shader_FromProto()
{
	if (FAILED(D3DXCreateEffectFromFile(Get_Graphic_Device(),
		m_tFilePath, nullptr, nullptr, 0, nullptr, &m_pEffectShader, nullptr)))
	{
		MSG_BOX("쉐이더 변수 생성에 실패했습니다!");
		return E_FAIL;
	}
	return NOERROR;
}

void CShader::Set_Object_Matrix(const CHAR * pConstantKey, const D3DXMATRIX * pMatrix)
{
	m_pEffectShader->SetMatrix(pConstantKey, pMatrix);
}
void CShader::Set_Object_Texture(const CHAR * pConstantKey, const LPDIRECT3DTEXTURE9 pTexture)
{
	m_pEffectShader->SetTexture(pConstantKey, pTexture);
}




CComponent * CShader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, const TCHAR* pShaderPath)
{
	CShader* pInstance = new CShader(pGraphic_Device);
	if (FAILED(pInstance->Add_Shader_FromFile(pShaderPath))) {
		MSG_BOX("쉐이더 파일 생성 실패");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent * CShader::Clone()
{
	CShader* pInstance = new CShader(*this);
	if (FAILED(pInstance->Add_Shader_FromProto())) {
		MSG_BOX("복제하여 새로 생성하는 것에 실패");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
void CShader::Free()
{
	Engine::Safe_Release(m_pEffectShader);
}
