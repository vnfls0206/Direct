#include "stdafx.h"
#include "CUI_ManaBar.h"

#include "CComponent_Manager.h"

#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"

CUI_ManaBar::CUI_ManaBar(LPDIRECT3DDEVICE9 pGraphic_Device)
	: Engine::CGameObject(pGraphic_Device)
{
}
CUI_ManaBar::CUI_ManaBar(const CUI_ManaBar & rhs)
	: Engine::CGameObject(rhs)
{
}

HRESULT CUI_ManaBar::Initialize_GameObject()
{
	return NOERROR;;
}

HRESULT CUI_ManaBar::Initialize_CloneObject()
{
	m_fTimeAcc = 0.f;

	m_pTransform = dynamic_cast<Engine::CTransform*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Transform"));
	if (m_pTransform == nullptr) {
		MSG_BOX("트랜스폼 컴포넌트가 NULLPTR 로 반환");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Transform", m_pTransform);

	m_pTransform->Set_Position(D3DXVECTOR3(0.f, -10.f, 0.5f));
	m_pTransform->Set_Scale(D3DXVECTOR3(100.f, 120.f, 1.f));
	m_pTransform->Set_Rotation(D3DXVECTOR3(D3DXToRadian(0.f), D3DXToRadian(-180.f), D3DXToRadian(0.f)));

	m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_UI_Bar"));
	if (m_pTextureCom == nullptr) {
		MSG_BOX("텍스처 컴포넌트가 NULLPTR 로 반환");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Texture", m_pTextureCom);

	m_pRenderCom = dynamic_cast<Engine::CRenderCom*>
		(m_pComponentMgr->Get_Component_In_Map_By_Proto(L"Component_RenderCom"));
	if (m_pRenderCom == nullptr) {
		MSG_BOX("렌더러 컴포넌트가 NULLPTR 로 반환");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Renderer", m_pRenderCom);

	m_pShaderCom = dynamic_cast<Engine::CShader*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Shader_Default"));
	if (m_pShaderCom == nullptr) {
		MSG_BOX("쉐이더 컴포넌트가 NULLPTR 로 반환");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Shader", m_pShaderCom);

	m_pBufferCom = dynamic_cast<Engine::CBuffer*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Buffer_RcTex"));
	if (m_pBufferCom == nullptr) {
		MSG_BOX("버퍼 컴포넌트가 NULLPTR 로 반환");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Buffer", m_pBufferCom);

	// 릭을 잡고 =->...
	// 플레이어객체를 띄워볼꺼야...-> 카메라를 플레이어에 고정시키고,
	// 움직일거야....
	// 객체를 하나 더만ㄷ르어서, 얘를 배경으로.... // 내일하자..

	return NOERROR;
}

void CUI_ManaBar::Update_GameObject(const float & fTimeDelta)
{
	m_pTransform->Make_LocalSpace_Matrix();

	D3DXVECTOR3 vPos = m_pTransform->Get_Position();
	if (*m_fPlayerMana <= 0)
		*m_fPlayerMana = 0;

	m_pTransform->Set_Scale(D3DXVECTOR3(790.f * (*m_fPlayerMana / 100), 15.f, 1.f));
	m_pTransform->Set_Position(D3DXVECTOR3(-395.f + (790.f * (*m_fPlayerMana / 100))/2, -165.f, vPos.z));
}

void CUI_ManaBar::LastUpdate_GameObject(const float & fTimeDelta)
{
	m_pRenderCom->Add_GameObject_To_List(Engine::CRenderCom::eRender_10, this);
	Ready_Shader(fTimeDelta);
}

void CUI_ManaBar::Render_GameObject()
{
	m_pShaderCom->Get_Effect()->Begin(0, 0);
	m_pShaderCom->Get_Effect()->BeginPass(1);

	if (FAILED(m_pBufferCom->Draw_Buffer()))
	{
		MSG_BOX("쉐이더 내에서 정점을 그리려는 데 실패했습니다.");
	}

	m_pShaderCom->Get_Effect()->EndPass();
	m_pShaderCom->Get_Effect()->End();
}

Engine::CGameObject * CUI_ManaBar::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CUI_ManaBar* pInstance = new CUI_ManaBar(pGraphic_Device);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		MSG_BOX("???");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

Engine::CGameObject * CUI_ManaBar::Clone()
{
	CUI_ManaBar* pInstance = new CUI_ManaBar(*this);
	if (FAILED(pInstance->Initialize_CloneObject()))
	{
		MSG_BOX("해당 클론 시 초기화에 실패");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

HRESULT CUI_ManaBar::Ready_Shader(const float& fTimedetla)
{
	D3DXMATRIX matView, matProj;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);

	D3DXMatrixOrthoLH(&matProj, ((float)WINCX), ((float)WINCY), 0.0f, 1.0f);

	m_pShaderCom->Set_Object_Matrix("g_matWorld", m_pTransform->Get_m_matLocal());
	m_pShaderCom->Set_Object_Matrix("g_matView", &matView);
	m_pShaderCom->Set_Object_Matrix("g_matProj", &matProj);

	m_pShaderCom->Get_Effect()->SetTexture("g_texture",
		m_pTextureCom->Get_Texture_From_Array_In_Vector(1));


	return NOERROR;
}

void CUI_ManaBar::Free()
{
}

void CUI_ManaBar::Get_PlayMana(float* Mana)
{
	m_fPlayerMana = Mana;
}
