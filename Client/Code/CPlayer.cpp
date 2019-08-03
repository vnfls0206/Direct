#include "stdafx.h"
#include "CPlayer.h"
#include "Client_Include.h"

#include "CComponent_Manager.h"

#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"
#include "CCollider.h"

#include "CSound_Manager.h"
#include "CKeyManager.h"

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
	m_fHp = 100.f;
	m_fMana = 100.f;


	m_pTransform = dynamic_cast<Engine::CTransform*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Transform"));
	if (m_pTransform == nullptr) {
		MSG_BOX("Ʈ������ ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Transform", m_pTransform);

	m_pTransform->Set_Position(D3DXVECTOR3(-200.f, 0.f, -5.f));
	m_pTransform->Set_Scale(D3DXVECTOR3(100.f, 100.f, 1.f));
	m_pTransform->Set_Rotation(D3DXVECTOR3(D3DXToRadian(0.f), D3DXToRadian(180.f), D3DXToRadian(0.f)));

	m_pCursor = m_pTransform->Set_ObjectPoint(m_pTransform->Get_Position(), m_pCursor);

	m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_Player"));
	if (m_pTextureCom == nullptr) {
		MSG_BOX("�ؽ�ó ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Texture", m_pTextureCom);

	m_pRenderCom = dynamic_cast<Engine::CRenderCom*>
		(m_pComponentMgr->Get_Component_In_Map_By_Proto(L"Component_RenderCom"));
	if (m_pRenderCom == nullptr) {
		MSG_BOX("������ ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Renderer", m_pRenderCom);

	m_pShaderCom = dynamic_cast<Engine::CShader*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Shader_Default"));
	if (m_pShaderCom == nullptr) {
		MSG_BOX("���̴� ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Shader", m_pShaderCom);

	m_pBufferCom = dynamic_cast<Engine::CBuffer*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Buffer_RcTex"));
	if (m_pBufferCom == nullptr) {
		MSG_BOX("���� ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Buffer", m_pBufferCom);

	m_pCollider = dynamic_cast<Engine::CCollider*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Collider"));
	if (m_pCollider == nullptr) {
		MSG_BOX("�ݶ��̴� ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Collider", m_pCollider);
	m_pCollider->Initialize_Collider(m_pTransform->Get_m_matLocal(), m_pTransform->Get_Scale());


	return NOERROR;
}

void CPlayer::Update_GameObject(const float & fTimeDelta)
{
	m_pTransform->Make_LocalSpace_Matrix();

	D3DXVECTOR3 vPos = m_pTransform->Get_Position();

	/*if (Engine::CKeyManager::GetInstance()->KeyPressing(VK_LEFT)) {
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
	}*/



	m_pTransform->Set_Position(vPos);
	/*
	if(Engine::CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		GetCursorPos(&m_pCursor);
		ScreenToClient(g_hWnd, &m_pCursor);
		m_pCursor.x = m_pCursor.x - WINCX / 2 + vPos.x;
		m_pCursor.y = WINCY / 2 - m_pCursor.y + vPos.y;
	}
	*/


	m_pTransform->MoveToMouse(m_pCursor, m_fMoveSpeed, fTimeDelta);
	m_pCollider->Set_ColliderPos(m_pTransform->Get_m_matLocal());
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
		MSG_BOX("���̴� ������ ������ �׸����� �� �����߽��ϴ�.");
	}

	m_pShaderCom->Get_Effect()->EndPass();
	m_pShaderCom->Get_Effect()->End();

	m_pCollider->Render_Collider();
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
		MSG_BOX("�ش� Ŭ�� �� �ʱ�ȭ�� ����");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayer::Set_pCursor(POINT m_cursor)
{
	m_pCursor = m_cursor;
}

void CPlayer::Play_Damage(float damage)
{
	m_fHp -= damage;
}

void CPlayer::Play_Use_Skill(float ManaCost)
{
	m_fMana -= ManaCost;
}

float * CPlayer::Get_Play_Hp()
{
	return &m_fHp;
}

float * CPlayer::Get_Play_Mana()
{
	return &m_fMana;
}

HRESULT CPlayer::Ready_Shader(const float& fTimedetla)
{
	D3DXMATRIX matView, matProj;
	Get_Graphic_Device()->GetTransform(D3DTS_VIEW, &matView);
	Get_Graphic_Device()->GetTransform(D3DTS_PROJECTION, &matProj);

	m_pShaderCom->Set_Object_Matrix("g_matWorld", m_pTransform->Get_m_matLocal());
	m_pShaderCom->Set_Object_Matrix("g_matView", &matView);
	m_pShaderCom->Set_Object_Matrix("g_matProj", &matProj);

	if (m_fTimeAcc >= 0.2f)
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

void CPlayer::Free()
{

	Engine::CGameObject::Free();
}
