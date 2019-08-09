#include "stdafx.h"
#include "CUI_HpBar.h"

#include "CGameObject_Manager.h"
#include "CComponent_Manager.h"
#include "Client_Include.h"

#include "CTransform.h"
#include "CTexture.h"
#include "CShader.h"
#include "CRenderCom.h"
#include "CBuffer_RcTex.h"

CUI_HpBar::CUI_HpBar(LPDIRECT3DDEVICE9 pGraphic_Device)
	: Engine::CGameObject(pGraphic_Device)
{
}
CUI_HpBar::CUI_HpBar(const CUI_HpBar & rhs)
	: Engine::CGameObject(rhs)
{
}

HRESULT CUI_HpBar::Initialize_GameObject()
{
	return NOERROR;;
}

HRESULT CUI_HpBar::Initialize_CloneObject()
{
	m_fTimeAcc = 0.f;
	m_pTransform = dynamic_cast<Engine::CTransform*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Transform"));
	if (m_pTransform == nullptr) {
		MSG_BOX("Ʈ������ ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Transform", m_pTransform);

	m_pTransform->Set_Position(D3DXVECTOR3(0.f, -10.f, 0.5f));
	m_pTransform->Set_Scale(D3DXVECTOR3(100.f, 120.f, 1.f));
	m_pTransform->Set_Rotation(D3DXVECTOR3(D3DXToRadian(0.f), D3DXToRadian(-180.f), D3DXToRadian(0.f)));

	m_pTextureCom = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_UI_Bar"));
	if (m_pTextureCom == nullptr) {
		MSG_BOX("�ؽ�ó ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	m_mapComponent.emplace(L"Com_Texture", m_pTextureCom);

	m_pTextureCom2 = dynamic_cast<Engine::CTexture*>
		(m_pComponentMgr->Get_Component_In_Map_By_Clone(L"Component_Texture_UI_Font"));
	if (m_pTextureCom2 == nullptr) {
		MSG_BOX("���� ������Ʈ�� NULLPTR �� ��ȯ");
		return E_FAIL;
	}
	
	m_mapComponent.emplace(L"Com_Texture2", m_pTextureCom2);

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

	// ���� ��� =->...
	// �÷��̾ü�� ���������...-> ī�޶� �÷��̾ ������Ű��,
	// �����ϰž�....
	// ��ü�� �ϳ� ���������, �긦 �������.... // ��������..

	return NOERROR;
}

void CUI_HpBar::Update_GameObject(const float & fTimeDelta)
{
	m_pTransform->Make_LocalSpace_Matrix();
	
	vPos = m_pObjectTransform->Get_Position();
	
	if (*m_fObjectHp <= 0)
		*m_fObjectHp += 100;

	m_pTransform->Set_Scale(D3DXVECTOR3(*m_fObjectHp, 15.f, 1.f));
	m_pTransform->Set_Position(D3DXVECTOR3(vPos.x - ( (100-*m_fObjectHp) / 2), vPos.y+60.f, vPos.z));
}

void CUI_HpBar::LastUpdate_GameObject(const float & fTimeDelta)
{
	m_pRenderCom->Add_GameObject_To_List(Engine::CRenderCom::eRender_10, this);
	Ready_Shader(fTimeDelta);
}

void CUI_HpBar::Render_GameObject()
{
	m_pShaderCom->Get_Effect()->Begin(0, 0);
	m_pShaderCom->Get_Effect()->BeginPass(0);

	if (FAILED(m_pBufferCom->Draw_Buffer()))
	{
		MSG_BOX("���̴� ������ ������ �׸����� �� �����߽��ϴ�.");
	}

	m_pShaderCom->Get_Effect()->EndPass();
	m_pShaderCom->Get_Effect()->End();

	if (*m_fObjectHp != m_fObjectHp2)
	{
		int Damage = m_fObjectHp2 - *m_fObjectHp;
		Set_Object_DamageFont(Damage);
		m_fObjectHp2 = *m_fObjectHp;
	}
}

Engine::CGameObject * CUI_HpBar::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CUI_HpBar* pInstance = new CUI_HpBar(pGraphic_Device);
	if (FAILED(pInstance->Initialize_GameObject()))
	{
		MSG_BOX("???");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

Engine::CGameObject * CUI_HpBar::Clone()
{
	CUI_HpBar* pInstance = new CUI_HpBar(*this);

	if (FAILED(pInstance->Initialize_CloneObject()))
	{
		MSG_BOX("�ش� Ŭ�� �� �ʱ�ȭ�� ����");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

HRESULT CUI_HpBar::Ready_Shader(const float& fTimedetla)
{
	D3DXMATRIX matView, matProj;
	Get_Graphic_Device()->GetTransform(D3DTS_VIEW, &matView);
	Get_Graphic_Device()->GetTransform(D3DTS_PROJECTION, &matProj);

	m_pShaderCom->Set_Object_Matrix("g_matWorld", m_pTransform->Get_m_matLocal());
	m_pShaderCom->Set_Object_Matrix("g_matView", &matView);
	m_pShaderCom->Set_Object_Matrix("g_matProj", &matProj);

	m_pShaderCom->Get_Effect()->SetTexture("g_texture",
		m_pTextureCom->Get_Texture_From_Array_In_Vector(0));
	 
	return NOERROR;
}

void CUI_HpBar::Free()
{
}

void CUI_HpBar::Set_Object_DamageFont(int Damage)
{
	Engine::CGameObject_Manager* pObjMgr = Engine::CGameObject_Manager::GetInstance();
	
	if (Damage < 10)
	{
		for (int i = 0; i < 20; i++)
		{
			pFont = pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_UI_Font")->Get_GameObject_In_List(i);
			m_pFont_Transform = dynamic_cast<Engine::CTransform*>(pFont->Get_Component_In_Map(L"Com_Transform"));
			fPos = m_pFont_Transform->Get_Position();
			if (fPos.z == -50.f)
			{
				m_pFont_Transform->Set_Position(D3DXVECTOR3(vPos.x + 40.f, vPos.y + 80.f, vPos.z));
				m_pFont_Shader = dynamic_cast<Engine::CShader*>(pFont->Get_Component_In_Map(L"Com_Shader"));
				m_pFont_Shader->Get_Effect()->SetTexture("g_texture",
					m_pTextureCom2->Get_Texture_From_Array_In_Vector(Damage));
				break;
			}
		}
	}

	else if(Damage>=10)
	{
		int Damage10, Damage1 , Count;

		Damage10 = Damage / 10;
		Damage1  = Damage % 10;
		Count = 0;

		for (int i = 0; i < 20; i++)
		{
			pFont = pObjMgr->Find_Layer((int)eScene_Stage1, L"Layer_UI_Font")->Get_GameObject_In_List(i);
			m_pFont_Transform = dynamic_cast<Engine::CTransform*>(pFont->Get_Component_In_Map(L"Com_Transform"));
			fPos = m_pFont_Transform->Get_Position();
			if (fPos.z == -50.f)
			{		
				if (Count == 0)
				{
					m_pFont_Transform->Set_Position(D3DXVECTOR3(vPos.x + 40.f - (20 * Count), vPos.y + 80.f, vPos.z));
					m_pFont_Shader = dynamic_cast<Engine::CShader*>(pFont->Get_Component_In_Map(L"Com_Shader"));
					m_pFont_Shader->Get_Effect()->SetTexture("g_texture",
						m_pTextureCom2->Get_Texture_From_Array_In_Vector(Damage1));
				}
				else if (Count == 1)
				{
					m_pFont_Transform->Set_Position(D3DXVECTOR3(vPos.x + 40.f - (20 * Count), vPos.y + 80.f, vPos.z));
					m_pFont_Shader = dynamic_cast<Engine::CShader*>(pFont->Get_Component_In_Map(L"Com_Shader"));
					m_pFont_Shader->Get_Effect()->SetTexture("g_texture",
						m_pTextureCom2->Get_Texture_From_Array_In_Vector(Damage10));
				}
				else
					break;
				++Count;
			}
		}
	}
}

void CUI_HpBar::Get_Object_Transform(Engine::CTransform * vTransform, float* HP)
{
	m_pObjectTransform = vTransform;
	m_fObjectHp = HP;
	m_fObjectHp2 = *HP;
}
