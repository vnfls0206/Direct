#include "stdafx.h"
#include "CScene_Stage.h"

#include "Client_Enum.h"

#include "CGameObject_Manager.h"
#include "CComponent_Manager.h"
#include "CKeyManager.h"

#include "CGraphic_Device.h"
#include "CSound_Manager.h"
#include "CTimerMgr.h"
#include "CTimer.h"

#include "CMonster.h"

#include "CTransform.h"
#include "CCollider.h"
#include "CStatic_Camera.h"
#include "CPlayer.h"
#include "CUI_Card.h"
#include "CUI_HpBar.h"
#include "CUI_ManaBar.h"




CScene_Stage::CScene_Stage(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CScene(pGraphic_Device)
	, m_pTimerMgr(Engine::CTimerMgr::GetInstance())
{
}

void CScene_Stage::Delete_Empty_GameObject_In_vector()
{
	for (int i = 0; i < m_vecAllylist->Get_List_Size(); i++)
	{
		if (m_vecAllylist->Get_GameObject_In_List(i) == nullptr)
		{
			m_vecAllylist->Delete_GameObject_In_Layer(i);
		}
	}

	for (int i = 0; i < m_vecEnemylist->Get_List_Size(); i++)
	{
		if (m_vecEnemylist->Get_GameObject_In_List(i) == nullptr)
		{
			m_vecEnemylist->Delete_GameObject_In_Layer(i);
		}
	}

	for (int i = 0; i < m_vecEtclist->Get_List_Size(); i++)
	{
		if (m_vecEtclist->Get_GameObject_In_List(i) == nullptr)
		{
			m_vecEtclist->Delete_GameObject_In_Layer(i);
		}
	}

}

void CScene_Stage::Check_Attack()
{
	Engine::CGameObject* pGameObject;
	for (int i = 0; i < m_vecAllylist->Get_List_Size(); i++)
	{
		pGameObject = m_vecAllylist->Get_GameObject_In_List(i);
		Engine::CCollider* AllyCollider = dynamic_cast<Engine::CCollider*>((pGameObject)->Get_Component_In_Map(L"Com_Collider"));
		CMonster* AllyMonster = dynamic_cast<CMonster*>(pGameObject);

		//������ų� ���ݵ����� ���� ��ü�� ���ؼ�, ���� ���°� �ƴ� ��� �ƹ��͵� ���� ����
		if (pGameObject == nullptr) { continue; }	
		if(AllyMonster->Is_Can_Attack()) { continue; }
		if (!((AllyMonster->Get_State() == eLEFT_ATTACK) || (AllyMonster->Get_State() == eUP_ATTACK) || 
			(AllyMonster->Get_State() == eRIGHT_ATTACK) || (AllyMonster->Get_State() == eDOWN_ATTACK)))	{continue; }

		//���� ���� ����
		//����� �ݶ��̴� ���� �浹, ���Ŀ� ���� ������ �ݶ��̴� ���� �浹�� ���� ���
		if (AllyCollider->Check_Collision_OBB(dynamic_cast<Engine::CCollider*>(AllyMonster->Get_Target()->Get_Component_In_Map(L"Com_Collider"))))
		{
			//�浿 ���� ��(���� ���� ��)������ ó�� ex)hp ����
		}

		//��������
		//����� �ݶ��̴� ���� �浹, ���Ŀ� ���� ������ �ݶ��̴� ���� �浹�� ���� ���
		CMonster* EnemyMonster;
		for (int j = 0; j < m_vecEnemylist->Get_List_Size(); j++)
		{
			EnemyMonster = dynamic_cast<CMonster*>(m_vecEnemylist->Get_GameObject_In_List(j));
			//��ü�� ���ų� ��Ȱ��ȭ�� ��� �ƹ��͵� ��������
			if(EnemyMonster == nullptr) { continue; }
			if(EnemyMonster->Get_State() == eInactive) { continue; }

			if (AllyCollider->Check_Collision_OBB(dynamic_cast<Engine::CCollider*>(EnemyMonster->Get_Component_In_Map(L"Com_Collider"))))
			{
				//�浿 ���� ��(���� ���� ��)������ ó�� ex)hp ����
			}
		}

	}

	for (int i = 0; i < m_vecEnemylist->Get_List_Size(); i++)
	{
		pGameObject = m_vecEnemylist->Get_GameObject_In_List(i);
		Engine::CCollider* EnemyCollider = dynamic_cast<Engine::CCollider*>((pGameObject)->Get_Component_In_Map(L"Com_Collider"));
		CMonster* EnemyMonster = dynamic_cast<CMonster*>(pGameObject);

		if (pGameObject == nullptr) { continue; }
		if (!EnemyMonster->Is_Can_Attack()) { continue; }
		if (!((EnemyMonster->Get_State() == eLEFT_ATTACK) || (EnemyMonster->Get_State() == eUP_ATTACK) || 
			(EnemyMonster->Get_State() == eRIGHT_ATTACK) || (EnemyMonster->Get_State() == eDOWN_ATTACK))) { continue; }

		//���� ���� ����
		//����� �ݶ��̴� ���� �浹, ���Ŀ� ���� ������ �ݶ��̴� ���� �浹�� ���� ���
		if (EnemyCollider->Check_Collision_OBB(dynamic_cast<Engine::CCollider*>(EnemyMonster->Get_Target()->Get_Component_In_Map(L"Com_Collider"))))
		{
			//�浿 ���� ��(���� ���� ��)������ ó�� ex)hp ����
		}

		//��������
		//����� �ݶ��̴� ���� �浹, ���Ŀ� ���� ������ �ݶ��̴� ���� �浹�� ���� ���
		CMonster* AllyMonster;
		for (int j = 0; j < m_vecAllylist->Get_List_Size(); j++)
		{
			AllyMonster = dynamic_cast<CMonster*>(m_vecAllylist->Get_GameObject_In_List(j));
			//��ü�� ���ų� ��Ȱ��ȭ�� ��� �ƹ��͵� ��������
			if (AllyMonster == nullptr) { continue; }
			if (AllyMonster->Get_State() == eInactive) { continue; }
			if (EnemyCollider->Check_Collision_OBB(dynamic_cast<Engine::CCollider*>(AllyMonster->Get_Component_In_Map(L"Com_Collider"))))
			{
				//�浿 ���� ��(���� ���� ��)������ ó�� ex)hp ����
			}
		}
	}
}

HRESULT CScene_Stage::Initialize_Scene()
{
	Engine::CGameObject_Manager* pObjMgr = Engine::CGameObject_Manager::GetInstance();
	if (pObjMgr == nullptr) {
		return E_FAIL;
	}

	pObjMgr->AddRef();

	Engine::CGameObject* pCamera = pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_StaticCamera",
		(int)eScene_Stage1, L"Layer_StaticCamera");
	ETC_GameObject_List.push_back(pCamera);

	pPlayer = pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Player",
		(int)eScene_Stage1, L"Layer_Player");
	Good_GameObject_List.push_back(pPlayer);

	Engine::CGameObject* pPlayer1 = pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Enemy",
		(int)eScene_Stage1, L"Layer_Enemy");
	Evil_GameObject_List.push_back(pPlayer1);

	ETC_GameObject_List.push_back((pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Back",
		(int)eScene_Stage1, L"Layer_Back")));
	Evil_GameObject_List.push_back((pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Rinel",
		(int)eScene_Stage1, L"Layer_Monster")));

	for (int a = 0; a < 6; a++)
	{
		ETC_GameObject_List.push_back(pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_UI_Card",
			(int)eScene_Stage1, L"Layer_UI_Card"));
		Engine::CGameObject* pUI_Card = pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_UI_Card")->Get_GameObject_In_List(a);
		dynamic_cast<CUI_Card*>(pUI_Card)->Set_CardInfo(D3DXVECTOR3(-345.0f + (100 * a), -235.0f, 0.5f), a);
	}

	ETC_GameObject_List.push_back(pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_UI_HpBar",
		(int)eScene_Stage1, L"Layer_UI_HpBar"));
	Engine::CGameObject* pUI_HpBar = pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_UI_HpBar")->Get_GameObject_In_List(0);
	dynamic_cast<CUI_HpBar*>(pUI_HpBar)->Get_Object_Transform
	(dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform")), 
		dynamic_cast<CPlayer*>(pPlayer)->Get_Play_Hp());


	Engine::CGameObject* pUI_ManaBar = pObjMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_UI_ManaBar",
		(int)eScene_Stage1, L"Layer_UI_ManaBar");
	ETC_GameObject_List.push_back(pUI_ManaBar);
	dynamic_cast<CUI_ManaBar*>(pUI_ManaBar)->Get_PlayMana(dynamic_cast<CPlayer*>(pPlayer)->Get_Play_Mana());

	//Engine::CTransform* pCameraTransform = dynamic_cast<Engine::CTransform*>(pCamera->Get_Component_In_Map(L"Com_Transform"));

	dynamic_cast<CStatic_Camera*>(pCamera)->Get_Player_Transform
	(dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform")));

	//D3DXVECTOR3 vecCameraPos = pCameraTransform->Get_Position();
	//vecCameraPos.z -= 50.f;
	//pCameraTransform->Set_Position(vecCameraPos);

	Engine::CTransform* pTransform = dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform"));
	Engine::CTransform* pTransform1 = dynamic_cast<Engine::CTransform*>(pPlayer1->Get_Component_In_Map(L"Com_Transform"));
	pTransform->Set_Position({-200.f, 180.f, 0.f});
	pTransform1->Set_Position({200.f, 180.f, 0.f});

	dynamic_cast<CStatic_Camera*>(pCamera)->Get_Player_Transform
	(dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform")));
	
	Engine::Safe_Release(pObjMgr);

	CSound_Manager::GetInstance()->PlayBGM(L"Adam Levine - Lost Stars Lyrics.mp3");

	return NOERROR;
}

void CScene_Stage::Update_Scene(const float & fTimeDelta)
{
	if (Engine::CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		Engine::CTransform* pPlayer_Tr = dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform"));

		POINT temp_pCursor = {0, 0};
		GetCursorPos(&temp_pCursor);
		ScreenToClient(g_hWnd, &temp_pCursor);
		temp_pCursor.x = temp_pCursor.x - WINCX / 2 + pPlayer_Tr->Get_Position().x;
		temp_pCursor.y = WINCY / 2 - temp_pCursor.y + pPlayer_Tr->Get_Position().y;

		D3DXVECTOR3 ETC_List_Vector, Evil_List_Vector;

		ETC_List_Vector.x = temp_pCursor.x - pPlayer_Tr->Get_Position().x;
		ETC_List_Vector.y = temp_pCursor.y - pPlayer_Tr->Get_Position().y;
		ETC_List_Vector.z = 1.f;

		Evil_List_Vector.x = temp_pCursor.x;
		Evil_List_Vector.y = temp_pCursor.y;
		Evil_List_Vector.z = 1.f;

		Engine::CGameObject* Target_ = Get_GameObject_From_List_By_Position(Evil_List_Vector, Evil_GameObject_List, 0);
		Engine::CGameObject* Target__ = Get_GameObject_From_List_By_Position(ETC_List_Vector, ETC_GameObject_List, 2);
		Engine::CGameObject* Target___;


		if (Target__ != nullptr)
		{
			if (Target__->Tag  == L"Layer_UI_Card")
			{
				switch (m_fUiCheck)
				{
				case 1:
					dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(1);
					break;
				case 2:
					dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(13);
					break;
				case 3:
					dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(5);
					break;
				case 4:
					dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(10);
					break;
				case 5:
					dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(25);
					break;
				case 6:
					dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(50);
					break;
				default:
					break;
				}
			}
		}
		else if (Target_ != nullptr)
		{
			MSG_BOX("clicked Enemy object");
		}

		else
		{
			dynamic_cast<CPlayer*>(pPlayer)->Set_pCursor(temp_pCursor);
		}
	}

	Engine::CGameObject_Manager* pObjMgr = Engine::CGameObject_Manager::GetInstance();
	Engine::CGameObject* pPlayer = pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_Player")->Get_GameObject_In_List(0);
	Engine::CGameObject* pPlayer1 = pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_Enemy")->Get_GameObject_In_List(0);
	CStatic_Camera* pCamera = static_cast<CStatic_Camera*>(
		pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_StaticCamera")->Get_GameObject_In_List(0));
	Engine::CCollider* pCollider = static_cast<Engine::CCollider*>(pPlayer->Get_Component_In_Map(L"Com_Collider"));
	Engine::CCollider* pCollider1 = static_cast<Engine::CCollider*>(pPlayer1->Get_Component_In_Map(L"Com_Collider"));
	Engine::CTransform* pTransform= static_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform"));



	if (pCollider->Check_Collision_OBB(pCollider1))
	{
		//MSG_BOX("1");
		//pTransform->Set_Position(pTransform->Get_Position() - D3DXVECTOR3(100.f, 100.f, 0.f));
		if (m_fTimeAcc >= 0.001f)
		{
			dynamic_cast<CPlayer*>(pPlayer)->Play_Damage(1);
			pCamera->Set_Camera_Zoom(m_fZoomRatio);
			if (m_fZoomRatio < 3.f)
			{
				m_fZoomRatio += 0.01f;
				m_pTimerMgr->Get_Timer_Info(L"Timer_60")->Set_BulletTime(.3f);
			}
			else if (m_fZoomRatio >= 3.f)
			{
				m_fZoomRatio = 1.f;
				m_pTimerMgr->Get_Timer_Info(L"Timer_60")->Set_BulletTime(1.f);
			}
			m_fTimeAcc = 0.f;
		}
		m_fTimeAcc += fTimeDelta;
	}
	
	return;
}

void CScene_Stage::Render_Scene()
{
	return;
}

CScene_Stage * CScene_Stage::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CScene_Stage* pInstance = new CScene_Stage(pGraphic_Device);
	if (FAILED(pInstance->Initialize_Scene()))
	{
		MSG_BOX("null print here");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

Engine::CGameObject* CScene_Stage::Get_GameObject_From_List_By_Position(D3DXVECTOR3 Positon, vector<Engine::CGameObject*> p_List, int Begin)
{

	Engine::CGameObject* Return_GameObject = nullptr;

	for (int i = Begin; i < p_List.size(); i++)
	{
		Engine::CTransform* pTransform = dynamic_cast<Engine::CTransform*>(p_List[i]->Get_Component_In_Map(L"Com_Transform"));

		if (pTransform != nullptr)
		{
			D3DXMATRIX* matLocal = pTransform->Get_m_matLocal();

			D3DXVECTOR3 vecRight, vecUp, vecLook, vecPos;
			memcpy(&vecRight, &matLocal->_11, sizeof(D3DXVECTOR3));
			memcpy(&vecUp, &matLocal->_21, sizeof(D3DXVECTOR3));
			memcpy(&vecLook, &matLocal->_31, sizeof(D3DXVECTOR3));
			memcpy(&vecPos, &matLocal->_41, sizeof(D3DXVECTOR3));

			D3DXVECTOR3 vecMin, vecMax;

			//vecMin = vecPos - (vecRight + vecUp + vecLook) / 2.f;
			//vecMax = (vecRight + vecUp + vecLook) / 2.f + vecPos;

			D3DXVECTOR3 position = pTransform->Get_Position();
			D3DXVECTOR3 scale = pTransform->Get_Scale();

			//memcpy(&position, &pTransform->Get_Position, sizeof(D3DXVECTOR3));
			//memcpy(&scale, &pTransform->Get_Scale, sizeof(D3DXVECTOR3));


			if ((position.x - scale.x / 2) <= Positon.x && Positon.x <= (position.x + scale.x / 2) && (position.y - scale.y / 2) <= Positon.y && Positon.y <= (position.y + scale.y / 2))
			{
				m_fUiCheck = i-1;
				Return_GameObject = p_List[i];
			}
		}

	}


	return Return_GameObject;

}

void CScene_Stage::Free()
{
	Engine::CScene::Free();
	return;
}
