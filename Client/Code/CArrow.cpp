#include "stdafx.h"
#include "CArrow.h"
#include "Client_Extern.h"

#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"
#include "CCollider.h"

#include "CGameObject_Manager.h"
#include "CComponent_Manager.h"

#include "CPlayer.h"
#include "CMonster.h"

int g_iCount_Arrow = 0;

CArrow::CArrow(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}

CArrow::CArrow(const CArrow & rhs)
	: CGameObject(rhs)
{
}

HRESULT CArrow::Initialize_GameObject()
{
	
	return NOERROR;
}

HRESULT CArrow::Initialize_CloneObject()
{
	m_pTransform = dynamic_cast<Engine::CTransform*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Transform"));
	if (m_pTransform == nullptr) {
		MSG_BOX("Transform Clone return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Transform", m_pTransform);

	m_pTransform->Set_Position(D3DXVECTOR3(0.f, 0.f, 0.f));
	m_pTransform->Set_Scale(D3DXVECTOR3(10.f, 20.f, 1.f));
	m_pTransform->Set_Rotation(D3DXVECTOR3(D3DXToRadian(0.f), D3DXToRadian(180.f), D3DXToRadian(0.f)));

	m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_Arrow"));
	if (m_pTextureCom == nullptr) {
		MSG_BOX("Texture Clone return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Texture", m_pTextureCom);

	m_pRenderCom = dynamic_cast<Engine::CRenderCom*>
		(m_pComponentMgr->Get_Component_In_Map_By_Proto(L"Component_RenderCom"));
	if (m_pRenderCom == nullptr) {
		MSG_BOX("RenderCom Proto return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Renderer", m_pRenderCom);

	m_pShaderCom = dynamic_cast<Engine::CShader*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Shader_Default"));
	if (m_pShaderCom == nullptr) {
		MSG_BOX("Shader Clone return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Shader", m_pShaderCom);

	m_pBufferCom = dynamic_cast<Engine::CBuffer*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Buffer_RcTex"));
	if (m_pBufferCom == nullptr) {
		MSG_BOX("Buffer Clone return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Buffer", m_pBufferCom);

	m_pCollider = dynamic_cast<Engine::CCollider*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Collider"));
	if (m_pCollider == nullptr) {
		MSG_BOX("Coliider Clone return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Collider", m_pCollider);

	m_pCollider->Initialize_Collider(m_pTransform->Get_m_matLocal());
	m_pCollider->Set_ColliderPos(m_pTransform->Get_m_matLocal());
	return NOERROR;
}

void CArrow::Update_GameObject(const float & fTimeDelta)
{
	if (m_pTarget == nullptr)
	{
		return;
	}
	Engine::CTransform* pTransform = dynamic_cast<Engine::CTransform*>(m_pTarget->Get_Component_In_Map(L"Com_Transform"));
	D3DXVECTOR3 dir = pTransform->Get_Position() - m_pTransform->Get_Position();
	D3DXVec3Normalize(&dir, &dir);
	if (pTransform->Get_Position().x > m_pTransform->Get_Position().x)
	{
		m_pTransform->Set_Rotation(D3DXVECTOR3(0.f, 180.f,
			-acosf(D3DXVec3Dot(&dir, &D3DXVECTOR3(0.f, 1.f, 0.f)))));
	}
	else
	{
		m_pTransform->Set_Rotation(D3DXVECTOR3(0.f, 180.f,
			acosf(D3DXVec3Dot(&dir, &D3DXVECTOR3(0.f, 1.f, 0.f)))));
	}

	D3DXVECTOR3 vPos = m_pTransform->Get_Position();
	vPos.x += dir.x * m_fMoveSpeed * fTimeDelta;
	vPos.y += dir.y * m_fMoveSpeed * fTimeDelta;
	//vPos.z += dir.z * m_fMoveSpeed * fTimeDelta;

	m_pTransform->Set_Position(vPos);
	m_pTransform->Make_LocalSpace_Matrix();
	m_pCollider->Set_ColliderPos(m_pTransform->Get_m_matLocal());

}

void CArrow::LastUpdate_GameObject(const float & fTimeDelta)
{
	if (m_pTarget == nullptr)
	{
		return;
	}
	Engine::CCollider* pCollider= dynamic_cast<Engine::CCollider*>(m_pTarget->Get_Component_In_Map(L"Com_Collider"));
	if (m_pCollider->Check_Collision_OBB(pCollider))
	{
		if (m_pTarget->Tag == L"Layer_Enemy")
		{
			dynamic_cast<CMonster*>(m_pTarget)->Hit(m_uiDamage);
			Set_Target(nullptr);
		}
		else if (m_pTarget->Tag == L"Layer_Player")
		{
			dynamic_cast<CPlayer*>(m_pTarget)->Hit(m_uiDamage);
			Set_Target(nullptr);
		}
		else
		{
			Set_Target(nullptr);
		}
	}

	m_pRenderCom->Add_GameObject_To_List(Engine::CRenderCom::eRender_4, this);
	Ready_Shader(fTimeDelta);
}

void CArrow::Render_GameObject()
{
	if (m_pTarget == nullptr)
	{
		return;
	}
	m_pShaderCom->Get_Effect()->Begin(0, 0);
	m_pShaderCom->Get_Effect()->BeginPass(0);

	if (FAILED(m_pBufferCom->Draw_Buffer()))
	{
		MSG_BOX("Draw_Buffer failed.");
	}

	m_pShaderCom->Get_Effect()->EndPass();
	m_pShaderCom->Get_Effect()->End();

	m_pCollider->Render_Collider(255, 0, 0, 255);
}


HRESULT CArrow::Ready_Shader(const float& fTimedetla)
{
	D3DXMATRIX matView, matProj;
	Get_Graphic_Device()->GetTransform(D3DTS_VIEW, &matView);
	Get_Graphic_Device()->GetTransform(D3DTS_PROJECTION, &matProj);

	m_pShaderCom->Set_Object_Matrix("g_matWorld", m_pTransform->Get_m_matLocal());
	m_pShaderCom->Set_Object_Matrix("g_matView", &matView);
	m_pShaderCom->Set_Object_Matrix("g_matProj", &matProj);


	m_pShaderCom->Get_Effect()->SetTexture("g_texture",
		m_pTextureCom->Get_Texture_From_Array_In_Vector(0));

	return NOERROR;
}
/*
int CArrow::Count_Arrow()
{
	if (g_iCount_Arrow >= Arrow_Count)
	{
		g_iCount_Arrow = 0;
	}
	return g_iCount_Arrow++;
}
*/
void CArrow::Set_Damage(UINT uiDamage) { m_uiDamage = uiDamage; }

void CArrow::Set_Target(Engine::CGameObject * pTarget)
{
	m_pTarget = pTarget;
}

void CArrow::Set_Position(D3DXVECTOR3 vecPos)
{
	m_pTransform->Set_Position(vecPos);
}

Engine::CGameObject * CArrow::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CArrow* pInstance = new CArrow(pGraphic_Device);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		MSG_BOX("Arrow Initialize Failed");
		Engine::Safe_Release(pInstance);
	}

	return pInstance;
}

Engine::CGameObject * CArrow::Clone()
{
	CArrow* pInstance = new CArrow(*this);
	if (FAILED(pInstance->Initialize_CloneObject()))
	{
		MSG_BOX("Arrow Clone Initialize Failed");
		Engine::Safe_Release(pInstance);
	}

	return pInstance;
}

void CArrow::Free()
{
	Engine::Safe_Release(m_pTransform);
	Engine::Safe_Release(m_pBufferCom);
	Engine::Safe_Release(m_pTextureCom);
	Engine::Safe_Release(m_pShaderCom);
	Engine::Safe_Release(m_pRenderCom);
	Engine::Safe_Release(m_pCollider);

	Engine::CGameObject::Free();
}
