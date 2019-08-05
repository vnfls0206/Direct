#include "stdafx.h"
#include "CMonster.h"

#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"
#include "CCollider.h"

#include "CGameObject_Manager.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphic_Device)
	: Engine::CGameObject(pGraphic_Device)
	, m_pObjMgr(Engine::CGameObject_Manager::GetInstance())
{
}
CMonster::CMonster(const CMonster & rhs)
	: Engine::CGameObject(rhs)
	, m_pObjMgr(rhs.m_pObjMgr)
{
}

eMonsterState CMonster::Get_Current_State() { return m_Current_State; }
Engine::CGameObject * CMonster::Get_Target() { return Target; }
void CMonster::Set_Target(Engine::CGameObject * pTarget)
{
	if (pTarget == nullptr)
	{
		return;
	}
	Target = pTarget;
}

bool CMonster::Get_Attack_Able() { return IsCanAttack; }

HRESULT CMonster::Ready_Shader(const float& fTimedetla)
{
	D3DXMATRIX matView, matProj;
	Get_Graphic_Device()->GetTransform(D3DTS_VIEW, &matView);
	Get_Graphic_Device()->GetTransform(D3DTS_PROJECTION, &matProj);

	m_pShaderCom->Set_Object_Matrix("g_matWorld", m_pTransform->Get_m_matLocal());
	m_pShaderCom->Set_Object_Matrix("g_matView", &matView);
	m_pShaderCom->Set_Object_Matrix("g_matProj", &matProj);


	if (m_fTimeAcc >= m_Info.m_State_Info[(int)m_Current_State].m_Motion_Time)
	{
		if (m_iCurIndex >= m_Info.m_State_Info[(int)m_Current_State].Max_Texture_Num) {
			//m_iCurIndex = m_Info.m_State_Info[m_Current_State].Min_Texture_Num;
			Update_Current_State();
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

void CMonster::Update_Current_State()
{
	D3DXVECTOR3 M_Position = m_pTransform->Get_Position();
	D3DXVECTOR3 P_Position = m_pPlayer_Transform->Get_Position();

	unsigned long distance = Get_Distance(M_Position, P_Position);
	eDirection direction = Get_Direction(M_Position, P_Position);



	if (distance > m_Info.Detect_Range)
	{
		if(direction == eLEFT)
			m_Current_State = eLEFT_IDLE;
		else if (direction == eUP)
			m_Current_State = eUP_IDLE;
		else if (direction == eRIGHT)
			m_Current_State = eRIGHT_IDLE;
		else if (direction == eDOWN)
			m_Current_State = eDOWN_IDLE;
	}
	else if (m_Info.Detect_Range >= distance && distance > m_Info.Attack_Range)
	{
		if (direction == eLEFT)
			m_Current_State = eLEFT_TRACE;
		else if (direction == eUP)
			m_Current_State = eUP_TRACE;
		else if (direction == eRIGHT)
			m_Current_State = eRIGHT_TRACE;
		else if (direction == eDOWN)
			m_Current_State = eDOWN_TRACE;
	}
	else if (distance <= m_Info.Attack_Range)
	{
		D3DXMATRIX* vPos = m_pTransform->Get_m_matLocal();
		if (direction == eLEFT)
		{
			m_Current_State = eLEFT_ATTACK;
			//m_pCollider_AttackRange->Set_ColliderPos(vPos);
		}
		else if (direction == eUP)
		{
			m_Current_State = eUP_ATTACK;
			//m_pCollider_AttackRange->Set_ColliderPos(vPos);
		}
		else if (direction == eRIGHT)
		{
			m_Current_State = eRIGHT_ATTACK;
			//m_pCollider_AttackRange->Set_ColliderPos(vPos);
		}
		else if (direction == eDOWN)
		{
			m_Current_State = eDOWN_ATTACK;
			//m_pCollider_AttackRange->Set_ColliderPos(vPos);
		}
		IsCanAttack = true;
	}

	m_iCurIndex = m_Info.m_State_Info[m_Current_State].Min_Texture_Num;


}
