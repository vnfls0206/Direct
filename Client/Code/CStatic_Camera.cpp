#include "stdafx.h"
#include "CStatic_Camera.h"
#include "CTransform.h"

CStatic_Camera::CStatic_Camera(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}
CStatic_Camera::CStatic_Camera(const CStatic_Camera & rhs)
	: CCamera(rhs)
{
}



HRESULT CStatic_Camera::Initialize_GameObject()
{
	return NOERROR;
}
HRESULT CStatic_Camera::Initialize_Camera_Matrix(Engine::DESC_VIEW tmpDESC_VIEW, Engine::DESC_PROJ tmpDESC_PROJ)
{
	CCamera::Initialize_View_Proj_Matrix(tmpDESC_VIEW, tmpDESC_PROJ);
	CCamera::Calculate_View_Proj_Matrix();
	return NOERROR;
}




void CStatic_Camera::Update_GameObject(const float & fTimeDelta)
{
	CCamera::Get_View_DESC().m_vAt = D3DXVECTOR3(0.f, 0.f, 0.f);
	CCamera::Get_View_DESC().m_vEye = D3DXVECTOR3( 
		CCamera::Get_View_DESC().m_vAt.x,
		CCamera::Get_View_DESC().m_vAt.y + 0.1f,
		CCamera::Get_View_DESC().m_vAt.z - 40.f);

	CCamera::Calculate_View_Proj_Matrix();
}
void CStatic_Camera::LastUpdate_GameObject(const float & fTimeDelta)
{
}
void CStatic_Camera::Render_GameObject()
{
}

Engine::CGameObject * CStatic_Camera::Create(LPDIRECT3DDEVICE9 pGraphic_Device, 
	Engine::DESC_VIEW tmpDESC_VIEW, Engine::DESC_PROJ tmpDESC_PROJ)
{
	CStatic_Camera* pCamera = new CStatic_Camera(pGraphic_Device);
	if (FAILED(pCamera->Initialize_GameObject()))
	{
		MSG_BOX("ī�޶� ������Ʈ�� �ʱ�ȭ�ϴµ� �����߽��ϴ�.");
		Engine::Safe_Release(pCamera);
	}
	if (FAILED(pCamera->Initialize_Camera_Matrix(tmpDESC_VIEW, tmpDESC_PROJ)))
	{
		MSG_BOX("ī�޶� ������Ʈ�� ����� �ʱ�ȭ�ϴµ� �����߽��ϴ�.");
		Engine::Safe_Release(pCamera);
	}
	return pCamera;
}

Engine::CGameObject * CStatic_Camera::Clone()
{
	return new CStatic_Camera(*this);
}

void CStatic_Camera::Free()
{

}

void CStatic_Camera::Get_Player_Transform(Engine::CTransform * vTransform)
{
	if (vTransform == nullptr)
		MSG_BOX("�ش� Ʈ�������� ���������Դϴ�.");
	m_pPlayerTransform = vTransform;
}

