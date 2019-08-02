#include "stdafx.h"
#include "CMonster.h"

#include "CComponent_Manager.h"
#include "CGameObject_Manager.h"


#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"


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
	m_pPlayer_Transform = dynamic_cast<Engine::CTransform*>(pPlayer->Get_Component_In_Map(L"Com_Transform"));


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

		break;
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
