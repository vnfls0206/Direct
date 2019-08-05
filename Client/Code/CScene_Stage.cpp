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
#include "CSwordMonster.h"
#include "CBowMonster.h"

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
	, m_pGameObjectMgr(Engine::CGameObject_Manager::GetInstance())
{
}

/*
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
		Engine::CCollider* AllyCollider = dynamic_cast<Engine::CCollider*>((pGameObject)->Get_Component_In_Map(L"Com_Collider_AttackRange"));
		CMonster* AllyMonster = dynamic_cast<CMonster*>(pGameObject);

		//������ų� ���ݵ����� ���� ��ü�� ���ؼ�, ���� ���°� �ƴ� ��� �ƹ��͵� ���� ����
		if (pGameObject == nullptr) { continue; }	
		if(!(AllyMonster->Get_Attack_Able() && (pGameObject->Tag == L"Layer_Ranger"))) { continue; }
		if (!((AllyMonster->Get_Current_State() == eLEFT_ATTACK) || (AllyMonster->Get_Current_State() == eUP_ATTACK) ||
			(AllyMonster->Get_Current_State() == eRIGHT_ATTACK) || (AllyMonster->Get_Current_State() == eDOWN_ATTACK)))	{continue; }

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
			if(EnemyMonster->Get_Current_State() == eInactive) { continue; }

			if (AllyCollider->Check_Collision_OBB(dynamic_cast<Engine::CCollider*>(EnemyMonster->Get_Component_In_Map(L"Com_Collider"))))
			{
				//�浿 ���� ��(���� ���� ��)������ ó�� ex)hp ����
			}
		}

	}

	for (int i = 0; i < m_vecEnemylist->Get_List_Size(); i++)
	{
		pGameObject = m_vecEnemylist->Get_GameObject_In_List(i);
		Engine::CCollider* EnemyCollider = dynamic_cast<Engine::CCollider*>((pGameObject)->Get_Component_In_Map(L"Com_Collider_AttackRange"));
		CMonster* EnemyMonster = dynamic_cast<CMonster*>(pGameObject);

		if (pGameObject == nullptr) { continue; }
		if (!EnemyMonster->Get_Attack_Able()) { continue; }
		if (!((EnemyMonster->Get_Current_State() == eLEFT_ATTACK) || (EnemyMonster->Get_Current_State() == eUP_ATTACK) ||
			(EnemyMonster->Get_Current_State() == eRIGHT_ATTACK) || (EnemyMonster->Get_Current_State() == eDOWN_ATTACK))) { continue; }

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
			if (AllyMonster->Get_Current_State() == eInactive) { continue; }
			if (EnemyCollider->Check_Collision_OBB(dynamic_cast<Engine::CCollider*>(AllyMonster->Get_Component_In_Map(L"Com_Collider"))))
			{
				//�浿 ���� ��(���� ���� ��)������ ó�� ex)hp ����
			}
		}
	}
}
*/

HRESULT CScene_Stage::Initialize_Scene()
{
	if (m_pGameObjectMgr == nullptr) {
		return E_FAIL;
	}

	m_pGameObjectMgr->AddRef();

	Engine::CGameObject* pCamera = m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_StaticCamera",
		(int)eScene_Stage1, L"Layer_StaticCamera");

	pPlayer = m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Player",
		(int)eScene_Stage1, L"Layer_Player");

	Engine::CGameObject* pPlayer1 = m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Enemy",
		(int)eScene_Stage1, L"Layer_Enemy");
	Evil_GameObject_List.push_back(pPlayer1);

	ETC_GameObject_List.push_back(
		(m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_Back",
		(int)eScene_Stage1, L"Layer_Back")));
	
	Engine::CGameObject* monster = (m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_SwordMonster",
		(int)eScene_Stage1, L"Layer_Monster"));
	Evil_GameObject_List.push_back(monster);
	Engine::CTransform* pTransform = dynamic_cast<Engine::CTransform*>(monster->Get_Component_In_Map(L"Com_Transform"));
	pTransform->Set_Position(D3DXVECTOR3(200.f, 180.f, 0.f));

	monster = (m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_BowMonster",
		(int)eScene_Stage1, L"Layer_Monster"));
	Evil_GameObject_List.push_back(monster);
	pTransform = dynamic_cast<Engine::CTransform*>(monster->Get_Component_In_Map(L"Com_Transform"));
	pTransform->Set_Position(D3DXVECTOR3(0.f, 0.f, 0.f));
	

	for (int a = 0; a < 6; a++)
	{
		m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_UI_Card",
			(int)eScene_Stage1, L"Layer_UI_Card");
		Engine::CGameObject* pUI_Card = m_pGameObjectMgr->Find_Layer((int)eScene_Stage1, L"Layer_UI_Card")->Get_GameObject_In_List(a);
		dynamic_cast<CUI_Card*>(pUI_Card)->Set_CardInfo(D3DXVECTOR3(-350.0f + (100 * a), -230.0f, 0.5f), a);
	}

	for (int a = 0; a < 20; a++)
	{
		m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_UI_Font",
			(int)eScene_Stage1, L"Layer_UI_Font");
	}

	m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_UI_HpBar",
		(int)eScene_Stage1, L"Layer_UI_HpBar");
	Engine::CGameObject* pUI_HpBar = m_pGameObjectMgr->Find_Layer((int)eScene_Stage1, L"Layer_UI_HpBar")->Get_GameObject_In_List(0);
	dynamic_cast<CUI_HpBar*>(pUI_HpBar)->Get_Object_Transform
	(dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform")), 
		dynamic_cast<CPlayer*>(pPlayer)->Get_Play_Hp());


	Engine::CGameObject* pUI_ManaBar = m_pGameObjectMgr->Copy_Proto_GameObject_To_Layer((int)eScene_Static, L"GameObject_Proto_UI_ManaBar",
		(int)eScene_Stage1, L"Layer_UI_ManaBar");
	dynamic_cast<CUI_ManaBar*>(pUI_ManaBar)->Get_PlayMana(dynamic_cast<CPlayer*>(pPlayer)->Get_Play_Mana());

	//Engine::CTransform* pCameraTransform = dynamic_cast<Engine::CTransform*>(pCamera->Get_Component_In_Map(L"Com_Transform"));

	dynamic_cast<CStatic_Camera*>(pCamera)->Get_Player_Transform
	(dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform")));

	pTransform = dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform"));
	pTransform->Set_Position(D3DXVECTOR3(-200.f, 400.f, 0.f));





	dynamic_cast<CStatic_Camera*>(pCamera)->Get_Player_Transform
	(dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform")));
	
	Engine::Safe_Release(m_pGameObjectMgr);

	CSound_Manager::GetInstance()->PlayBGM(L"Adam Levine - Lost Stars Lyrics.mp3");

	return NOERROR;
}

void CScene_Stage::Update_Scene(const float & fTimeDelta)
{
	Engine::CGameObject* pCamera = m_pGameObjectMgr->Find_Layer((int)eScene_Stage1, L"Layer_StaticCamera")->Get_GameObject_In_List(0);

	if (Engine::CKeyManager::GetInstance()->KeyDown(VK_LBUTTON))
	{
		Engine::CTransform* pPlayer_Tr = dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform"));

		POINT temp_pCursor = {0, 0};
		GetCursorPos(&temp_pCursor);
		ScreenToClient(g_hWnd, &temp_pCursor);
		temp_pCursor.x = temp_pCursor.x - WINCX / 2 + pPlayer_Tr->Get_Position().x;
		temp_pCursor.y = WINCY / 2 - temp_pCursor.y + pPlayer_Tr->Get_Position().y;

		D3DXVECTOR3 UI_List_Vector, Evil_List_Vector;

		UI_List_Vector.x = temp_pCursor.x - pPlayer_Tr->Get_Position().x;
		UI_List_Vector.y = temp_pCursor.y - pPlayer_Tr->Get_Position().y;
		UI_List_Vector.z = 1.f;

		Evil_List_Vector.x = temp_pCursor.x;
		Evil_List_Vector.y = temp_pCursor.y;
		Evil_List_Vector.z = 1.f;

		Engine::CGameObject* Target_ = Get_GameObject_From_List_By_Position(Evil_List_Vector, L"Layer_Enemy");
		Engine::CGameObject* Target__ = Get_GameObject_From_List_By_Position(UI_List_Vector, L"Layer_UI_Card");


	
		if (Target_ != nullptr)
		{
			MSG_BOX("clicked Enemy object");
		}
		else if (Target__ != nullptr)
		{
			switch (m_fUiCheck)
			{
			case 1:
				dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(1);
				dynamic_cast<CPlayer*>(pPlayer)->Play_Damage(1);
				break;
			case 2:
				dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(5);
				dynamic_cast<CPlayer*>(pPlayer)->Play_Damage(5);
				break;
			case 3:
				dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(10);
				dynamic_cast<CPlayer*>(pPlayer)->Play_Damage(10);
				break;
			case 4:
				dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(25);
				dynamic_cast<CPlayer*>(pPlayer)->Play_Damage(25);
				break;
			case 5:
				dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(50);
				dynamic_cast<CPlayer*>(pPlayer)->Play_Damage(50);
				break;
			case 6:
				dynamic_cast<CPlayer*>(pPlayer)->Play_Use_Skill(13);
				dynamic_cast<CPlayer*>(pPlayer)->Play_Damage(13);
				break;
			default:
				break;
			}
		}
		else
		{
			if (temp_pCursor.x <= -250.f)
			{
				temp_pCursor.x = -250.f;
			}
			else if (temp_pCursor.x >= 250.f)
			{
				temp_pCursor.x = 250.f;
			}
			dynamic_cast<CPlayer*>(pPlayer)->Set_pCursor(temp_pCursor);
		}
	}
	if (Engine::CKeyManager::GetInstance()->KeyDown(0x51)) //q
	{
		m_pTimerMgr->Get_Timer_Info(L"Timer_60")->Set_BulletTime(.3f);
	}

	if (Engine::CKeyManager::GetInstance()->KeyPressing(0x57)) //w
	{
		if (m_fTimeAcc >= 0.001f)
		{
			dynamic_cast<Engine::CCamera*>(pCamera)->Set_Camera_Zoom(m_fZoomRatio);
			if (m_fZoomRatio < 3.f)
			{
				m_fZoomRatio += 0.01f;
			}
			m_fTimeAcc = 0.f;
		}
		m_fTimeAcc += fTimeDelta;
	}

	if (Engine::CKeyManager::GetInstance()->KeyDown(0x45)) //e
	{
	}

	if (Engine::CKeyManager::GetInstance()->KeyDown(0x52)) //r
	{
		m_fZoomRatio = 1.f;
		dynamic_cast<Engine::CCamera*>(pCamera)->Set_Camera_Zoom(m_fZoomRatio); dynamic_cast<Engine::CCamera*>(pCamera)->Set_Camera_Zoom(m_fZoomRatio);
		m_pTimerMgr->Get_Timer_Info(L"Timer_60")->Set_BulletTime(1.f);
	}

	//CStatic_Camera* pCamera = static_cast<CStatic_Camera*>(
	//	m_pGameObjectMgr->Find_Layer((int)eScene_Stage1, L"Layer_StaticCamera")->Get_GameObject_In_List(0));


	/*
	if (pCollider->Check_Collision_OBB(pCollider1))
	{
		//MSG_BOX("1");
		//pTransform->Set_Position(pTransform->Get_Position() - D3DXVECTOR3(100.f, 100.f, 0.f));
		if (m_fTimeAcc >= 0.001f)
		{
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
	*/
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

Engine::CGameObject* CScene_Stage::Get_GameObject_From_List_By_Position(D3DXVECTOR3 Positon, const TCHAR* tag)
{

	Engine::CLayer* Checked_Layer = m_pGameObjectMgr->Find_Layer((int)eScene_Stage1, tag);

	for (int i = 0; i < Checked_Layer->Get_List_Size(); i++)
	{
		Engine::CGameObject* pObj = Checked_Layer->Get_GameObject_In_List(i);

		Engine::CTransform* pTransform = 
			dynamic_cast<Engine::CTransform*>(pObj->Get_Component_In_Map(L"Com_Transform"));

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
				m_fUiCheck = i+1 ;
				return Checked_Layer->Get_GameObject_In_List(i);
			}
		}

	}


	return nullptr;

}

void CScene_Stage::Summon_Monster(Engine::CGameObject * pGameObject, int iSummonNum)
{

}





void CScene_Stage::Free()
{
	Engine::CScene::Free();
	return;
}
