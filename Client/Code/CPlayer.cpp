#include "stdafx.h"
#include "CPlayer.h"

#include "CComponent_Manager.h"

#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"

#include "CKeyManager.h"
#include "CSound_Manager.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device)
	: Engine::CGameObject(pGraphic_Device)
{
}
CPlayer::CPlayer(const CPlayer & rhs)
	: Engine::CGameObject(rhs)
{

}



HRESULT CPlayer::Initialize_GameObject()
{
	return NOERROR;
}

HRESULT CPlayer::Initialize_CloneObject()
{
	m_fTimeAcc = 0.f;

	m_pTransform = dynamic_cast<Engine::CTransform*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Transform"));
	if (m_pTransform == nullptr) {
		MSG_BOX("트랜스폼 컴포넌트가 NULLPTR 로 반환");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Transform", m_pTransform);

	m_pTransform->Set_Position(D3DXVECTOR3(0.f, 0.f, -5.f));
	m_pTransform->Set_Scale(D3DXVECTOR3(500.f, 500.f, 1.f));
	m_pTransform->Set_Rotation(D3DXVECTOR3(D3DXToRadian(0.f), D3DXToRadian(-180.f), D3DXToRadian(0.f)));

	m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_Player"));
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

void CPlayer::Update_GameObject(const float & fTimeDelta)
{
	m_pTransform->Make_LocalSpace_Matrix();

	D3DXVECTOR3 vPos = m_pTransform->Get_Position();

	if (Engine::CKeyManager::GetInstance()->KeyPressing(VK_LEFT)) {
		vPos.x -= m_fMoveSpeed * fTimeDelta;
	}
	if (Engine::CKeyManager::GetInstance()->KeyPressing(VK_RIGHT)) {
		vPos.x += m_fMoveSpeed * fTimeDelta;
	}
	if (Engine::CKeyManager::GetInstance()->KeyUp(VK_UP)) {
		CSound_Manager::GetInstance()->PlaySound(L"Shot.wav", CSound_Manager::ePlayer);
		vPos.y += 5000.f * fTimeDelta;
	}
	if (Engine::CKeyManager::GetInstance()->KeyDown(VK_DOWN)) {
		CSound_Manager::GetInstance()->PlaySound(L"ChainSaw1.wav", CSound_Manager::ePlayer);
		vPos.y -= 5000.f * fTimeDelta;
	}


	m_pTransform->Set_Position(vPos);

}

void CPlayer::LastUpdate_GameObject(const float & fTimeDelta)
{
	m_pRenderCom->Add_GameObject_To_List(Engine::CRenderCom::eRender_3, this);
	Ready_Shader(fTimeDelta);
}

void CPlayer::Render_GameObject()
{
	m_pShaderCom->Get_Effect()->Begin(0 ,0);
	m_pShaderCom->Get_Effect()->BeginPass(0);

	if (FAILED(m_pBufferCom->Draw_Buffer()))
	{
		MSG_BOX("쉐이더 내에서 정점을 그리려는 데 실패했습니다.");
	}

	m_pShaderCom->Get_Effect()->EndPass();
	m_pShaderCom->Get_Effect()->End();
}

Engine::CGameObject * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CPlayer* pInstance = new CPlayer(pGraphic_Device);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		MSG_BOX("???");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
Engine::CGameObject * CPlayer::Clone()
{
	CPlayer* pInstance = new CPlayer(*this);
	if (FAILED(pInstance->Initialize_CloneObject()))
	{
		MSG_BOX("해당 클론 시 초기화에 실패");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

HRESULT CPlayer::Ready_Shader(const float& fTimedetla)
{
	D3DXMATRIX matView, matProj;
	Get_Graphic_Device()->GetTransform(D3DTS_VIEW, &matView);
	Get_Graphic_Device()->GetTransform(D3DTS_PROJECTION, &matProj);

	m_pShaderCom->Set_Object_Matrix("g_matWorld", m_pTransform->Get_m_matLocal());
	m_pShaderCom->Set_Object_Matrix("g_matView", &matView);
	m_pShaderCom->Set_Object_Matrix("g_matProj", &matProj);

	if (m_fTimeAcc >= 0.5f)
	{
		if (m_iCurIndex >= m_iMaxIndex) {
			m_iCurIndex = m_iMinIndex;
		}
		else
			m_iCurIndex++;

		m_fTimeAcc = 0.f;
	}
	else
		m_fTimeAcc += fTimedetla;

	m_pShaderCom->Get_Effect()->SetTexture("g_texture",
		m_pTextureCom->Get_Texture_From_Array_In_Vector(m_iCurIndex));
	
	return NOERROR;
}
