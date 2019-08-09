#include "stdafx.h"
#include "CMonster.h"

#include "CComponent_Manager.h"

#include "CLayer.h"
#include "CGameObject_Manager.h"
#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"
#include "CCollider.h"


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
	Target = pTarget;
}

bool CMonster::Get_Attack_Able() { return IsCanAttack; }

void CMonster::Hit(UINT Damage)
{
	if (Damage < 0)
	{
		return;
	}
	if (m_Info.uiHP <= Damage)
	{
		m_Info.uiHP = 0;
		m_Current_State = eDie;
	}
	else if (m_Info.uiHP >= Damage)
	{
		m_Info.uiHP -= Damage;
	}
}









bool CMonster::Node_Check(Engine::CGameObject_Manager* GM, list<node*> checked_List, D3DXVECTOR3 t_Position)	//t_position = target_p
{
	bool a;


	for_each(checked_List.begin(), checked_List.end(),
		[&](node* temp_node)
	{
		if (t_Position == temp_node->position)
			a =  false;

	});

	if(a ==false)
		return false;


	/*for (auto iter = checked_List.begin(); iter != checked_List.end(); iter++)
	{
		node* temp_node = *iter;
		if (t_Position == temp_node->position)
			return false;
	}*/

	const TCHAR* Tags[] = { L"Layer_Player", L"Layer_Enemy" };

	D3DXVECTOR3 p_scale = m_pTransform->Get_Scale();	//노드의 크기는 이 몬스터의 크기만큼으로 결정해준다
	D3DXVECTOR3 p_Min_Vector = D3DXVECTOR3( t_Position.x - p_scale.x / 2 , t_Position.y - p_scale.y / 2, 0.f );
	D3DXVECTOR3 p_Max_Vector = D3DXVECTOR3( t_Position.x + p_scale.x / 2 , t_Position.y + p_scale.y / 2, 0.f );

	for (int i = 0; i < sizeof(Tags) / sizeof(Tags[0]); i++)
	{
		Engine::CLayer* Checked_Layer = GM->Find_Layer((int)eScene_Stage1, Tags[i]);

		for (int j = 0; j < Checked_Layer->Get_List_Size(); j++)
		{
			CGameObject* Target_obj = Checked_Layer->Get_GameObject_In_List(j);

			Engine::CTransform* pTransform =
				dynamic_cast<Engine::CTransform*>(Target_obj->Get_Component_In_Map(L"Com_Transform"));

			if (pTransform != nullptr)
			{
				D3DXVECTOR3 c_position = i != 0 ? dynamic_cast<CMonster*>(Target_obj)->Get_Dex_Position() : pTransform->Get_Position();
	
				D3DXVECTOR3 c_scale = pTransform->Get_Scale();

				D3DXVECTOR3 c_Min_Vector = { c_position.x - c_scale.x / 2 , c_position.y - c_scale.y / 2, 0.f };
				D3DXVECTOR3 c_Max_Vector = { c_position.x + c_scale.x / 2 , c_position.y + c_scale.y / 2, 0.f };

				if (!(c_Min_Vector.x >= p_Max_Vector.x ||
					c_Max_Vector.x <= p_Min_Vector.x ||
					c_Max_Vector.y <= p_Min_Vector.y ||
					c_Min_Vector.y >= p_Max_Vector.y) )
				{
					return false;

				}
	
	
			}


		}
	}
	


	return true;
}




UINT CMonster::Get_Hp() { return m_Info.uiHP; }

void CMonster::Die()
{
	//������� �� �� ����
	Free();
}



D3DXVECTOR3 CMonster::Get_Dex_Position()
{
	return Dex_Position;
}

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
	unsigned long distance = 9999;
	eDirection direction;
	Target = nullptr;
	const TCHAR* Tags[] = { L"Layer_Player" };

	for (int i = 0; i < sizeof(Tags) / sizeof(Tags[0]); i++)
	{
		Engine::CGameObject_Manager* GM = Engine::CGameObject_Manager::GetInstance();

		Engine::CLayer* Checked_Layer = GM->Find_Layer((int)eScene_Stage1, Tags[i]);

		for (int j = 0; j < Checked_Layer->Get_List_Size(); j++)
		{
			CGameObject* Target_obj = Checked_Layer->Get_GameObject_In_List(j);

			Engine::CTransform* pTransform =
				dynamic_cast<Engine::CTransform*>(Target_obj->Get_Component_In_Map(L"Com_Transform"));

			if (pTransform != nullptr)
			{
				float target_distance = Get_Distance(M_Position, pTransform->Get_Position());

				if (target_distance < distance)
				{
					Target = Target_obj;
					distance = target_distance;
					direction = Get_Direction(M_Position, pTransform->Get_Position());

				}



			}


		}
	}



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
		//D3DXMATRIX* vPos = m_pTransform->Get_m_matLocal();
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

void CMonster::Free()
{
	 Engine::Safe_Release(m_pTransform);
	 Engine::Safe_Release(m_pBufferCom);
	 Engine::Safe_Release(m_pTextureCom);
	 Engine::Safe_Release(m_pShaderCom);
	 Engine::Safe_Release(m_pRenderCom);
	 Engine::Safe_Release(m_pCollider);
	 Engine::Safe_Release(m_pCollider_AttackRange);

	Engine::CGameObject::Free();
}
