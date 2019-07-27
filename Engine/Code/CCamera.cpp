#include "stdafx.h"
#include "CCamera.h"

USING(Engine)

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CGameObject(pGraphic_Device)
{
}
CCamera::CCamera(const CCamera & rhs)
	: CGameObject(rhs),
	stView(rhs.stView),
	stProj(rhs.stProj),
	matView(rhs.matView),
	matProj(rhs.matProj)
{
}

void CCamera::Calculate_ViewSpaceMatrix()
{
	D3DXMatrixLookAtLH(&matView, &stView.m_vEye, &stView.m_vAt, &stView.m_vAxisY);		// �޼���ǥ�� // ���Լ��� �Ⱦ���, ����� ���巷�� �佺���̽�
	Get_Graphic_Device()->SetTransform(D3DTS_VIEW, &matView);
	// ������� => ����
	// 1. LookVec = At��ġ��, ������ ��.
	// 2. RightVec = LookVec��, 0,1,0 ���͸� ����
	// 3. RealUpVec = LookVec, RightVec ����
	// 4. ��ķ� �����
	// 5. ����� -> ��

	// D3DXVec3Cross( ,  , );
	// D3DXMatrixInverse( , nullptr, );

	//D3DXMatrixLookAtRH();		// ��������ǥ��


}

DESC_VIEW& CCamera::Get_View_DESC()
{
	return stView;
}



void CCamera::Calculate_ProjectionSpaceMatrix()
{
	D3DXMatrixOrthoLH(&matProj, 800.f, 600.f, stProj.m_fNear, stProj.m_fFar);
	Get_Graphic_Device()->SetTransform(D3DTS_PROJECTION, &matProj);
}
void CCamera::Initialize_View_Proj_Matrix(DESC_VIEW pDESC_VIEW, DESC_PROJ pDESC_PROJ)
{
	memcpy(&stView, &pDESC_VIEW, sizeof(pDESC_VIEW));
	memcpy(&stProj, &pDESC_PROJ, sizeof(pDESC_PROJ));
}
void CCamera::Calculate_View_Proj_Matrix()
{
	Calculate_ViewSpaceMatrix();
	Calculate_ProjectionSpaceMatrix();
}

void CCamera::Free()
{
}
