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

void CCamera::Set_Camera_Zoom(float fRatio)
{
	if (fRatio <= 0.f)
	{
		fRatio - 1.f;
	}
	m_fZoomRatio = fRatio;
}

void CCamera::Calculate_ViewSpaceMatrix()
{
	D3DXMatrixLookAtLH(&matView, &stView.m_vEye, &stView.m_vAt, &stView.m_vAxisY);		// 왼손좌표계 // 이함수를 안쓰고, 행렬을 만드렁와 뷰스페이스
	Get_Graphic_Device()->SetTransform(D3DTS_VIEW, &matView);
	// 제조방법 => 과제
	// 1. LookVec = At위치와, 내눈을 빼.
	// 2. RightVec = LookVec와, 0,1,0 벡터를 외적
	// 3. RealUpVec = LookVec, RightVec 외적
	// 4. 행렬로 만들기
	// 5. 역행렬 -> 끝

	// D3DXVec3Cross( ,  , );
	// D3DXMatrixInverse( , nullptr, );

	//D3DXMatrixLookAtRH();		// 오른손좌표계


}

DESC_VIEW& CCamera::Get_View_DESC()
{
	return stView;
}



void CCamera::Calculate_ProjectionSpaceMatrix()
{
	D3DXMatrixOrthoLH(&matProj, ((float)WINCX / m_fZoomRatio), ((float)WINCY / m_fZoomRatio), stProj.m_fNear, stProj.m_fFar);
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
