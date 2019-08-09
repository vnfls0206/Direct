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

#include <iostream>




CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphic_Device, MON_INFO m_mon_info)
	: Engine::CGameObject(pGraphic_Device)
{
	m_Info = m_mon_info;
}
CMonster::CMonster(const CMonster & rhs, MON_INFO m_mon_info)
	: Engine::CGameObject(rhs)
{
	m_Info = m_mon_info;
}



HRESULT CMonster::Initialize_GameObject()
{



	return NOERROR;
}

HRESULT CMonster::Initialize_CloneObject()
{
	Engine::CGameObject_Manager* pObjMgr = Engine::CGameObject_Manager::GetInstance();
	pPlayer = pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_Player")->Get_GameObject_In_List(0);
	//m_pPlayer_Transform = dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform"));


	m_fTimeAcc = 0.f;

	m_pTransform = dynamic_cast<Engine::CTransform*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Transform"));
	if (m_pTransform == nullptr) {
		MSG_BOX("Ʈ������ ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Transform", m_pTransform);

	m_pTransform->Set_Position(D3DXVECTOR3(0.f, -20.f, 0.f));
	m_pTransform->Set_Scale(D3DXVECTOR3(100.f, 100.f, 1.f));
	m_pTransform->Set_Rotation(D3DXVECTOR3(D3DXToRadian(0.f), D3DXToRadian(180.f), D3DXToRadian(0.f)));

	m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_Rinel"));
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


	Dex_Position = m_pTransform->Get_Position();

	Update_Current_State();	//���۽��ѹ� ���¸� �������ش�.

	return NOERROR;
}

void CMonster::Update_GameObject(const float & fTimeDelta)
{
	m_pTransform->Make_LocalSpace_Matrix();



	switch (m_Current_State)
	{
	case 0:
	case 1:
	case 2:
	case 3:

		break;
	case 4:
	case 5:
	case 6:
	case 7:
	{
		if (Get_Distance(m_pTransform->Get_Position(), Dex_Position) < 10)
		{

			Engine::CGameObject_Manager* GM = Engine::CGameObject_Manager::GetInstance();

			std::list<node*> openlist;	////open list, add unchecked node
			std::list<node*> closedlist;	//closed list, add checked node

			D3DXVECTOR3 Current_P = m_pTransform->Get_Position();
			D3DXVECTOR3 Target_P =
				dynamic_cast<Engine::CTransform*>(Target->Get_Component_In_Map(L"Com_Transform"))->Get_Position();

			//node Parent_node = { Current_P, 0, 0, nullptr };

			node *Selected_node = (node *)malloc(sizeof(node));

			Selected_node->position = Current_P;
			Selected_node->G = 0;
			Selected_node->H = 0;
			Selected_node->Parent_node = nullptr;

			openlist.push_back(Selected_node);


			for (int Finding_Range = 0; Finding_Range < 2; Finding_Range++)
			{
				node* Low_Cost_List = nullptr;

				//list<node*>::iterator iter = openlist.begin();

				for_each(openlist.begin(), openlist.end(),
					[&](node* temp_node)
				{
					if (Low_Cost_List == nullptr)
						Low_Cost_List = temp_node;
					else
					{
						if ((Low_Cost_List->G + Low_Cost_List->H) > (temp_node->G + temp_node->H))
						{
							Low_Cost_List = temp_node;
						}
					}

				});

				Selected_node = Low_Cost_List;	//select node, 

				float scale = m_pTransform->Get_Scale().x;


				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (!(i == 0 && j == 0))
						{
							D3DXVECTOR3 Node_Position = D3DXVECTOR3((Selected_node->position.x) + i * scale, (Selected_node->position.y) + j * scale, 0.f);

							if (Node_Check(GM, openlist, Node_Position))
							{
								node* m_node = (node *)malloc(sizeof(node));;

								unsigned int cost = (i*j) == -1 ? 14 : 10;

								m_node->position = Node_Position;
								m_node->H = abs(Node_Position.x - Target_P.x) + abs(Node_Position.y - Target_P.y);
								m_node->G = cost + Selected_node->G;
								m_node->Parent_node = Selected_node;

								openlist.push_back(m_node);

							}

						}


					}

				}

				closedlist.push_back(Selected_node);
				openlist.remove(Selected_node);	//Add self position, to closed list

			}
			Dex_Position = Selected_node->position;



			while (!openlist.empty())
			{
				auto iter = openlist.begin();
				delete[](*iter);
				openlist.erase(iter);
			}
			while (!closedlist.empty())
			{
				auto iter = closedlist.begin();
				delete[](*iter);
				closedlist.erase(iter);
			}

		}
		m_pTransform->MoveToPosition(Dex_Position, m_fMoveSpeed, fTimeDelta);


		break;
	}
	case 8:
	case 9:
	case 10:
	case 11:

		break;
	default:
		break;
	}

}

void CMonster::LastUpdate_GameObject(const float & fTimeDelta)
{
	m_pRenderCom->Add_GameObject_To_List(Engine::CRenderCom::eRender_4, this);
	Ready_Shader(fTimeDelta);
}

void CMonster::Render_GameObject()
{
	m_pShaderCom->Get_Effect()->Begin(0, 0);
	m_pShaderCom->Get_Effect()->BeginPass(0);

	if (FAILED(m_pBufferCom->Draw_Buffer()))
	{
		MSG_BOX("���̴� ������ ������ �׸����� �� �����߽��ϴ�.");
	}

	m_pShaderCom->Get_Effect()->EndPass();
	m_pShaderCom->Get_Effect()->End();
}



bool CMonster::Is_Can_Attack()
{
	return false;
}

eMonsterState CMonster::Get_State()
{
	return eMonsterState();
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
	D3DXVECTOR3 p_Min_Vector = { t_Position.x - p_scale.x / 2 , t_Position.y - p_scale.y / 2, 0.f };
	D3DXVECTOR3 p_Max_Vector = { t_Position.x + p_scale.x / 2 , t_Position.y + p_scale.y / 2, 0.f };

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


Engine::CGameObject * CMonster::Create(LPDIRECT3DDEVICE9 pGraphic_Device, MON_INFO m_mon_info)
{
	CMonster* pInstance = new CMonster(pGraphic_Device, m_mon_info);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		MSG_BOX("pInstance�� �������� �Դϴ�");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
Engine::CGameObject * CMonster::Clone()
{
	CMonster* pInstance = new CMonster(*this, this->m_Info);
	if (FAILED(pInstance->Initialize_CloneObject()))
	{
		MSG_BOX("�ش� Ŭ�� �� �ʱ�ȭ�� ����");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

eMonsterState CMonster::Get_Current_State()
{
	return m_Current_State;
}

Engine::CGameObject * CMonster::Get_Target()
{
	return Target;
}

bool CMonster::Get_Attack_Able()
{
	return IsCanAttack;
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


	if (m_fTimeAcc >= 0.1f)
	{
		if (m_iCurIndex >= m_Info.m_State_Info[m_Current_State].Max_Texture_Num) {
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
		if (direction == eLEFT)
			m_Current_State = eLEFT_ATTACK;
		else if (direction == eUP)
			m_Current_State = eUP_ATTACK;
		else if (direction == eRIGHT)
			m_Current_State = eRIGHT_ATTACK;
		else if (direction == eDOWN)
			m_Current_State = eDOWN_ATTACK;

		IsCanAttack = true;
	}

	m_iCurIndex = m_Info.m_State_Info[m_Current_State].Min_Texture_Num;

}
