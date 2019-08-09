#include "stdafx.h"
#include "CBowMonster.h"
#include "CArrow.h"

#include "stdafx.h"
#include "CBowMonster.h"

#include "CComponent_Manager.h"
#include "CGameObject_Manager.h"

#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"
#include "CCollider.h"

CBowMonster::CBowMonster(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CMonster(pGraphic_Device)
{
}
CBowMonster::CBowMonster(const CBowMonster& rhs)
	: CMonster(rhs)
{
}


HRESULT CBowMonster::Initialize_GameObject()
{
	return NOERROR;
}

HRESULT CBowMonster::Initialize_CloneObject()
{
	m_Info = { {{ 0.1f, 8, 15 }, { 0.1f, 24, 31 }, { 0.1f, 16, 23 }, { 0.1f, 0, 7 },
				{ 0.1f, 37, 41 }, { 0.1f, 47, 51 }, { 0.1f, 42, 46 }, { 0.1f, 32, 36 },
				{ 0.1f, 60, 66 }, { 0.1f, 75, 82 }, { 0.1f, 67, 74 }, { 0.1f, 52, 59 }},
				400, 250, 10, 120, 0.6f, -1, L"BowMon" };

	m_pPlayer_Transform = dynamic_cast<Engine::CTransform*>(m_pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_Player")->Get_GameObject_In_List(0)->
		Get_Component_In_Map(L"Com_Transform"));
	if (m_pPlayer_Transform == nullptr) {
		MSG_BOX("Player Transform return NULLPTR in CBowMonster");
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
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_Rinel"));
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

void CBowMonster::Update_GameObject(const float & fTimeDelta)
{
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


		for (int Finding_Range = 0; Finding_Range < 2; Finding_Range++)
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

			float scale = m_pTransform->Get_Scale().x + 10;


			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (!(i == 0 && j == 0))
					{
						D3DXVECTOR3 Node_Position = D3DXVECTOR3((Selected_node->position.x) + i * scale, (Selected_node->position.y) + j * scale, 0.f);

						if (Node_Check(GM, openlist, Node_Position))
						{
							NODE* m_node = (NODE *)malloc(sizeof(NODE));;

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
	m_pTransform->Make_LocalSpace_Matrix();
	m_pCollider->Set_ColliderPos(m_pTransform->Get_m_matLocal());
	m_pCollider_AttackRange->Set_ColliderPos(m_pTransform->Get_m_matLocal());
}

void CBowMonster::LastUpdate_GameObject(const float & fTimeDelta)
{
	m_pRenderCom->Add_GameObject_To_List(Engine::CRenderCom::eRender_4, this);
	Ready_Shader(fTimeDelta);
}

void CBowMonster::Render_GameObject()
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


void CBowMonster::Attack(const float& fTimeDelta)
{
	if ((m_fAttackTime >= 0.4f) || (m_fAttackTime < 0.5f))
	{
		//화살생성
		CArrow* arrow = dynamic_cast<CArrow*>(m_pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Arrow",
			(int)eScene_Stage1, L"Layer_Arrow"));
		arrow->Set_Damage(m_Info.uiAttackDamage);
		arrow->Set_Target(Target);
		arrow->Set_Position(m_pTransform->Get_Position());
		//CArrow::Create(Get_Graphic_Device(), Target);
	}
	else if (m_fAttackTime >= 0.5f)
	{
		m_fAttackTime = 0.f;
	}
	m_fAttackTime += fTimeDelta;
}

Engine::CGameObject * CBowMonster::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CBowMonster* pInstance = new CBowMonster(pGraphic_Device);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		MSG_BOX("CBowMonster GameObject Initialize failed");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
Engine::CGameObject * CBowMonster::Clone()
{
	CBowMonster* pInstance = new CBowMonster(*this);
	if (FAILED(pInstance->Initialize_CloneObject()))
	{
		MSG_BOX("CBowMonster Clone Initialize failed");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}
