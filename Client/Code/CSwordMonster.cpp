#include "stdafx.h"
#include "CSwordMonster.h"

#include "CComponent_Manager.h"
#include "CGameObject_Manager.h"


#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"
#include "CCollider.h"

#include "CPlayer.h"

CSwordMonster::CSwordMonster(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CMonster(pGraphic_Device)
{
}
CSwordMonster::CSwordMonster(const CSwordMonster& rhs)
	: CMonster(rhs)
{
}


HRESULT CSwordMonster::Initialize_GameObject()
{

	return NOERROR;
}

HRESULT CSwordMonster::Initialize_CloneObject()
{
	m_Info = { {{ 0.1f, 2, 2 }, { 0.1f, 0, 0 }, { 0.1f, 3, 3 }, { 0.1f, 1, 1 },
							 { 0.1f, 16, 21 }, { 0.1f, 4, 9 }, { 0.1f, 22, 27 }, { 0.5f, 10, 15 },
							 { 0.1f, 36, 39 }, { 0.1f, 28, 31 }, { 0.1f, 40, 43 }, { 0.1f, 32, 35 }},
							300, 150, 20, 200, 0.8f, 1, L"SwordMon" };
	//탐색범위 공격볌위 공격력 체력 딜레이 타입 이름

	m_pPlayer_Transform = dynamic_cast<Engine::CTransform*>(m_pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_Player")->Get_GameObject_In_List(0)->
		Get_Component_In_Map(L"Com_Transform"));
	if (m_pPlayer_Transform == nullptr) {
		MSG_BOX("Player_Transform return NULLPTR In Monster ");
		return E_FAIL;
	}

	m_fTimeAcc = 0.f;

	m_pTransform = dynamic_cast<Engine::CTransform*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Transform"));
	if (m_pTransform == nullptr) {
		MSG_BOX("Transform Clone return NULLPTR ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Transform", m_pTransform);

	m_pTransform->Set_Position(D3DXVECTOR3(0.f, 0.f, 0.f));
	m_pTransform->Set_Scale(D3DXVECTOR3(100.f, 100.f, 1.f));
	m_pTransform->Set_Rotation(D3DXVECTOR3(D3DXToRadian(0.f), D3DXToRadian(180.f), D3DXToRadian(0.f)));

	m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_SwordMonster"));
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

	m_pCollider_AttackRange = dynamic_cast<Engine::CCollider*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Collider"));
	if (m_pCollider_AttackRange == nullptr) {
		MSG_BOX("Coliider Clone return NULLPTR m_pCollider_AttackRange");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Collider_AttackRange", m_pCollider_AttackRange);
	
	Dex_Position = m_pTransform->Get_Position();

	Update_Current_State();

	m_pCollider->Initialize_Collider(m_pTransform->Get_m_matLocal());
	m_pCollider_AttackRange->Initialize_Collider(m_pTransform->Get_m_matLocal());

	return NOERROR;
}

void CSwordMonster::Update_GameObject(const float & fTimeDelta)
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
		Engine::CGameObject_Manager* GM = Engine::CGameObject_Manager::GetInstance();

		std::list<NODE*> openlist;	////open list, add unchecked node
		std::list<NODE*> closedlist;	//closed list, add checked node

		D3DXVECTOR3 Current_P = m_pTransform->Get_Position();
		D3DXVECTOR3 Target_P =
			dynamic_cast<Engine::CTransform*>(Target->Get_Component_In_Map(L"Com_Transform"))->Get_Position();

		//node Parent_node = { Current_P, 0, 0, nullptr };

		NODE *Selected_node = (NODE *)malloc(sizeof(NODE));

		Selected_node->position = Current_P;
		Selected_node->G = 0;
		Selected_node->H = 0;
		Selected_node->Parent_node = nullptr;

		openlist.push_back(Selected_node);


		for (int Finding_Range = 0; Finding_Range < 3; Finding_Range++)
		{
			NODE* Low_Cost_List = nullptr;

			//list<node*>::iterator iter = openlist.begin();

			for_each(openlist.begin(), openlist.end(),
				[&](NODE* temp_node)
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


			if (Selected_node == nullptr)
			{
				Clear_List(openlist);
				Clear_List(closedlist);

				return;
			}

			float scale = 10;


			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (!(i == 0 && j == 0))
					{
						D3DXVECTOR3 Node_Position = D3DXVECTOR3((Selected_node->position.x) + i * scale, (Selected_node->position.y) + j * scale, 0.f);

						if (Node_Check(GM, openlist, Node_Position))
						{
							unsigned int cost = (i*j) == -1 ? 14 : 10;


							NODE* m_node = (NODE *)malloc(sizeof(NODE));;

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


		Dex_Position = Selected_node->Parent_node->position;

		m_pTransform->MoveToPosition(Dex_Position, m_fMoveSpeed, fTimeDelta);


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

		break;
	case 8:
	case 9:
	case 10:
	case 11:

		break;
	default:
		break;
	}
	m_pCollider->Set_ColliderPos(m_pTransform->Get_m_matLocal());
	m_pCollider_AttackRange->Set_ColliderPos(m_pTransform->Get_m_matLocal(), 2.f);
}

void CSwordMonster::LastUpdate_GameObject(const float & fTimeDelta)
{
	m_pRenderCom->Add_GameObject_To_List(Engine::CRenderCom::eRender_4, this);
	Ready_Shader(fTimeDelta);
}

void CSwordMonster::Render_GameObject()
{
	m_pShaderCom->Get_Effect()->Begin(0, 0);
	m_pShaderCom->Get_Effect()->BeginPass(0);

	if (FAILED(m_pBufferCom->Draw_Buffer()))
	{
		MSG_BOX("Draw_Buffer failed.");
	}

	m_pShaderCom->Get_Effect()->EndPass();
	m_pShaderCom->Get_Effect()->End();

	m_pCollider->Render_Collider(255, 0, 255, 0);
	m_pCollider_AttackRange->Render_Collider(255, 255, 0, 0);
}


void CSwordMonster::Attack(const float& fTimeDelta)
{
	if ((m_fAttackTime >= 0.4f) || (m_fAttackTime < 0.5f))
	{
		if (m_pCollider_AttackRange->Check_Collision_OBB(dynamic_cast<Engine::CCollider*>(Target->Get_Component_In_Map(L"Com_Collider"))))
		{
			//hp감소
			if (Target->Tag == L"Layer_Player")
			{
				dynamic_cast<CMonster*>(Target)->Hit(m_Info.uiAttackDamage);
			}
			else if (Target->Tag == L"Layer_Enemy")
			{
				dynamic_cast<CPlayer*>(Target)->Hit(m_Info.uiAttackDamage);
			}
		}
	}
	else if (m_fAttackTime >= 0.5f)
	{
		m_fAttackTime = 0.f;
	}
	m_fAttackTime += fTimeDelta;
}

Engine::CGameObject * CSwordMonster::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CSwordMonster* pInstance = new CSwordMonster(pGraphic_Device);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		MSG_BOX("CSwordMonster GameObject Initialize failed");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
Engine::CGameObject * CSwordMonster::Clone()
{
	CSwordMonster* pInstance = new CSwordMonster(*this);
	if (FAILED(pInstance->Initialize_CloneObject()))
	{
		MSG_BOX("CSwordMonster Clone Initialize failed");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
