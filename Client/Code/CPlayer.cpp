#include "stdafx.h"
#include "CPlayer.h"
#include "Client_Include.h"

#include "CComponent_Manager.h"
#include "CGameObject_Manager.h"

#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"
#include "CCollider.h"

#include "CSound_Manager.h"
#include "CKeyManager.h"

#include "CArrow.h"

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
	m_pObjMgr = Engine::CGameObject_Manager::GetInstance();

	m_stInfo = { {{ 0.5f, 2, 2 }, { 0.5f, 0, 0 }, { 0.5f, 3, 3 }, { 0.5f, 1, 1 },
				{ 0.5f, 16, 21 }, { 0.5f, 4, 9 }, { 0.5f, 22, 27 }, { 0.5f, 10, 15 },
				{ 0.5f, 36, 39 }, { 0.5f, 28, 31 }, { 0.5f, 40, 43 }, { 0.5f, 32, 35 }},
				300, 30, 400, 25.f, 0.4f , L"Summoner" };
			//공격범위 공격력, 체력, 마나, 공격딜레이, 이름

	m_fTimeAcc = 0.f;
	m_stInfo.uiHP = 100;
	m_stInfo.fMana= 100.f;


	m_pTransform = dynamic_cast<Engine::CTransform*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Transform"));
	if (m_pTransform == nullptr) {
		MSG_BOX("Transform return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Transform", m_pTransform);

	m_pTransform->Set_Position(D3DXVECTOR3(200.f, 0.f, -5.f));
	m_pTransform->Set_Scale(D3DXVECTOR3(100.f, 100.f, 1.f));
	m_pTransform->Set_Rotation(D3DXVECTOR3(D3DXToRadian(0.f), D3DXToRadian(180.f), D3DXToRadian(0.f)));

	m_pCursor = m_pTransform->Set_ObjectPoint(m_pTransform->Get_Position(), m_pCursor);

	m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_Player"));
	if (m_pTextureCom == nullptr) {
		MSG_BOX("Texture return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Texture", m_pTextureCom);

	m_pRenderCom = dynamic_cast<Engine::CRenderCom*>
		(m_pComponentMgr->Get_Component_In_Map_By_Proto(L"Component_RenderCom"));
	if (m_pRenderCom == nullptr) {
		MSG_BOX("Render return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Renderer", m_pRenderCom);

	m_pShaderCom = dynamic_cast<Engine::CShader*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Shader_Default"));
	if (m_pShaderCom == nullptr) {
		MSG_BOX("Shader return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Shader", m_pShaderCom);

	m_pBufferCom = dynamic_cast<Engine::CBuffer*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Buffer_RcTex"));
	if (m_pBufferCom == nullptr) {
		MSG_BOX("Buffer return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Buffer", m_pBufferCom);

	m_pCollider = dynamic_cast<Engine::CCollider*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Collider"));
	if (m_pCollider == nullptr) {
		MSG_BOX("Collider return NULLPTR");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Collider", m_pCollider);
	m_pCollider->Initialize_Collider(m_pTransform->Get_m_matLocal());


	return NOERROR;
}

void CPlayer::Update_GameObject(const float & fTimeDelta)
{
	//D3DXVECTOR3 vPos = m_pTransform->Get_Position();

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

	//m_pTransform->Set_Position(vPos);
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
	m_pTransform->Make_LocalSpace_Matrix();
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
		MSG_BOX("Draw_Buffer failed in Player.");
	}

	m_pShaderCom->Get_Effect()->EndPass();
	m_pShaderCom->Get_Effect()->End();

	m_pCollider->Render_Collider(255, 0, 255, 0);
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
		MSG_BOX("Player failed Clone Initialization");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

void CPlayer::Set_pCursor(POINT m_cursor)
{
	m_pCursor = m_cursor;
}

void CPlayer::Play_Damage(UINT damage)
{
	if (m_stInfo.uiHP < damage)
		m_stInfo.uiHP = 0;
	else
		m_stInfo.uiHP -= damage;
}

void CPlayer::Play_Use_Skill(float ManaCost)
{
	m_stInfo.fMana -= ManaCost;
}

UINT * CPlayer::Get_Play_Hp()
{
	return &m_stInfo.uiHP;
}

float * CPlayer::Get_Play_Mana()
{
	return &m_stInfo.fMana;
}

void CPlayer::Set_Target(Engine::CGameObject * pTarget)
{
	m_pTarget = pTarget;
}

void CPlayer::Attack(const float& fTimeDelta)
{
	if ((m_fAttackTime >= 0.4f) || (m_fAttackTime < 0.5f))
	{
		//화살생성
		CArrow* arrow = dynamic_cast<CArrow*>(m_pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Arrow",
			(int)eScene_Stage1, L"Layer_Arrow"));
		arrow->Set_Damage(m_stInfo.uiAttackDamage);
		arrow->Set_Target(m_pTarget);
		arrow->Set_Position(m_pTransform->Get_Position());
		//CArrow::Create(Get_Graphic_Device(), Target);
	}
	else if (m_fAttackTime >= 0.5f)
	{
		m_fAttackTime = 0.f;
	}
	m_fAttackTime += fTimeDelta;
}

void CPlayer::Hit(UINT uiDamage)
{
	if (uiDamage < 0)
	{
		return;
	}
	if (m_stInfo.uiHP <= uiDamage)
	{
		m_stInfo.uiHP = 0;
		m_Current_State = eDie;
	}
	else if (m_stInfo.uiHP >= uiDamage)
	{
		m_stInfo.uiHP -= uiDamage;
	}
}

void CPlayer::Die()
{
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
	Engine::Safe_Release(m_pTransform);
	Engine::Safe_Release(m_pBufferCom);
	Engine::Safe_Release(m_pTextureCom);
	Engine::Safe_Release(m_pShaderCom);
	Engine::Safe_Release(m_pRenderCom);
	Engine::Safe_Release(m_pCollider);

	Engine::CGameObject::Free();
}
