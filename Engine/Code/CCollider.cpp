#include "stdafx.h"
#include "CCollider.h"
#include "math.h"

Engine::CCollider::CCollider(LPDIRECT3DDEVICE9 pDevice)
	: CComponent(pDevice)
{
}

Engine::CCollider::CCollider(const CCollider & rhs)
	: CComponent(rhs)
{
}

void Engine::CCollider::Initialize_Collider(D3DXVECTOR3* p_vecPos, DWORD dwVertexNum, DWORD dwFVF)
{
	D3DXComputeBoundingBox(p_vecPos, dwVertexNum, dwFVF, &vecMin, &vecMax);
	Center.x = (vecMin.x + vecMax.x) / 2.f;
	Center.y = (vecMin.y + vecMax.y) / 2.f;
	Center.z = (vecMin.z + vecMax.z) / 2.f;

	Extent.x = vecMax.x - Center.x;
	Extent.y = vecMax.y - Center.y;
	Extent.z = vecMax.z - Center.z;

	Axis[0] = {vecMax.x - vecMin.x, 0.f, 0.f};
	Axis[1] = {0.f, vecMax.y - vecMin.y, 0.f};
	Axis[2] = {0.f, 0.f, vecMax.z - vecMin.z};
	
	D3DXVec3Normalize(&Axis[0], &Axis[0]);
	D3DXVec3Normalize(&Axis[1], &Axis[1]);
	D3DXVec3Normalize(&Axis[2], &Axis[2]);
}

void Engine::CCollider::Set_ColliderPos(D3DXVECTOR3 * p_vecPos, DWORD dwVertexNum, DWORD dwFVF)
{
	D3DXComputeBoundingBox(p_vecPos, dwVertexNum, dwFVF, &vecMin, &vecMax);
	Center.x = (vecMin.x + vecMax.x) / 2.f;
	Center.y = (vecMin.y + vecMax.y) / 2.f;
	Center.z = (vecMin.z + vecMax.z) / 2.f;
}

bool Engine::CCollider::Check_Collision_OBB(Engine::CCollider* targetCollider)
{
	double C[3][3];
	double absC[3][3];
	double D[3];
	double R0, R1, R2;

	const double cutoff = 0.999999;		//부동소수점 오차 보정
	bool existsParallelPair = false;	//평행 축 검사, 평행한 축이 존재할 경우 6축검사로 판별가능

	D3DXVECTOR3 diff = this->Center - targetCollider->Center;	//두 콜라이더 중심의 거리

	for (int i = 0; i < 3; i++)
	{
		C[0][i] = D3DXVec3Dot(&this->Axis[0], &targetCollider->Axis[i]);	//값이 1, -1이 나올 경우 두 축은 서로 평행
		absC[0][i] = abs(C[0][i]);		//양수화
		if (absC[0][i] > cutoff)
		{
			existsParallelPair = true;
		}
	}

	D[0] = D3DXVec3Dot(&diff, &this->Axis[0]);	//diff를  this의 x축에 투영시킨 값
	R0 = abs(D[0]);
	R1 = this->Extent.x;
	R2 = (this->Extent.x * absC[0][0]) + (this->Extent.y * absC[0][1]) + (this->Extent.z * absC[0][2]);
	if (R0 > R1 + R2)
	{
		return false;
	}

	for (int i = 0; i < 3; i++)
	{
		C[1][i] = D3DXVec3Dot(&this->Axis[1], &targetCollider->Axis[i]);	//값이 1, -1이 나올 경우 두 축은 서로 평행
		absC[1][i] = abs(C[1][i]);		//양수화
		if (absC[1][i] > cutoff)
		{
			existsParallelPair = true;
		}
	}

	D[1] = D3DXVec3Dot(&diff, &this->Axis[1]);	//diff를  this의 y축에 투영시킨 값
	R0 = abs(D[1]);
	R1 = this->Extent.y;
	R2 = (this->Extent.x * absC[1][0]) + (this->Extent.y * absC[1][1]) + (this->Extent.z * absC[1][2]);
	if (R0 > R1 + R2)
	{
		return false;
	}

	for (int i = 0; i < 3; i++)
	{
		C[2][i] = D3DXVec3Dot(&this->Axis[2], &targetCollider->Axis[i]);	//값이 1, -1이 나올 경우 두 축은 서로 평행
		absC[2][i] = abs(C[2][i]);		//양수화
		if (absC[2][i] > cutoff)
		{
			existsParallelPair = true;
		}
	}

	D[2] = D3DXVec3Dot(&diff, &this->Axis[2]);	//diff를  this의 z축에 투영시킨 값
	R0 = abs(D[2]);
	R1 = this->Extent.z;
	R2 = (this->Extent.x * absC[2][0]) + (this->Extent.y * absC[2][1]) + (this->Extent.z * absC[2][2]);
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D3DXVec3Dot(&diff, &targetCollider->Axis[0]));	//diff를 targetCollider의 x축에 투영
	R1 = (this->Extent.x * absC[0][0]) + (this->Extent.y * absC[1][0]) + (this->Extent.z * absC[2][0]);
	R2 = targetCollider->Extent.x;
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D3DXVec3Dot(&diff, &targetCollider->Axis[1]));	//diff를 targetCollider의 y축에 투영
	R1 = (this->Extent.x * absC[0][1]) + (this->Extent.y * absC[1][1]) + (this->Extent.z * absC[2][1]);
	R2 = targetCollider->Extent.y;
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D3DXVec3Dot(&diff, &targetCollider->Axis[2]));	//diff를 targetCollider의 z축에 투영
	R1 = (this->Extent.x * absC[0][2]) + (this->Extent.y * absC[1][2]) + (this->Extent.z * absC[2][2]);
	R2 = targetCollider->Extent.z;
	if (R0 > R1 + R2)
	{
		return false;
	}

	if (existsParallelPair == true)		//x y z어느 한 축이라도 평행하면 6축 검사로 충분하기에 검사 종료
	{
		return true;
	}

	R0 = abs(D[2] * C[1][0] - D[1] * C[2][0]);
	R1 = this->Extent.y * absC[2][0] + this->Extent.z * absC[1][0];
	R2 = targetCollider->Extent.y * absC[0][2] + targetCollider->Extent.z * absC[0][1];
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D[2] * C[1][1] - D[1] * C[2][1]);
	R1 = this->Extent.y * absC[2][1] + this->Extent.z * absC[1][1];
	R2 = targetCollider->Extent.x * absC[0][2] + targetCollider->Extent.z * absC[0][0];
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D[2] * C[1][2] - D[1] * C[2][2]);
	R1 = this->Extent.y * absC[2][2] + this->Extent.z * absC[1][2];
	R2 = targetCollider->Extent.x * absC[0][1] + targetCollider->Extent.y * absC[0][0];
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D[0] * C[2][0] - D[2] * C[0][0]);
	R1 = this->Extent.x * absC[2][0] + this->Extent.z * absC[0][0];
	R2 = targetCollider->Extent.y * absC[1][2] + targetCollider->Extent.z * absC[1][1];
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D[0] * C[2][1] - D[2] * C[0][1]);
	R1 = this->Extent.x * absC[2][1] + this->Extent.z * absC[0][1];
	R2 = targetCollider->Extent.x * absC[1][2] + targetCollider->Extent.z * absC[1][0];
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D[0] * C[2][2] - D[2] * C[0][2]);
	R1 = this->Extent.x * absC[2][2] + this->Extent.z * absC[0][2];
	R2 = targetCollider->Extent.x * absC[1][1] + targetCollider->Extent.y * absC[1][0];
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D[1] * C[0][0] - D[0] * C[1][0]);
	R1 = this->Extent.x * absC[1][0] + this->Extent.y * absC[0][0];
	R2 = targetCollider->Extent.y * absC[2][2] + targetCollider->Extent.z * absC[2][1];
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D[1] * C[0][1] - D[0] * C[1][1]);
	R1 = this->Extent.x * absC[1][1] + this->Extent.y * absC[0][1];
	R2 = targetCollider->Extent.x * absC[2][2] + targetCollider->Extent.z * absC[2][0];
	if (R0 > R1 + R2)
	{
		return false;
	}

	R0 = abs(D[1] * C[0][2] - D[0] * C[1][2]);
	R1 = this->Extent.x * absC[1][2] + this->Extent.y * absC[0][2];
	R2 = targetCollider->Extent.x * absC[2][1] + targetCollider->Extent.y * absC[2][0];
	if (R0 > R1 + R2)
	{
		return false;
	}

	return true;
}

bool Engine::CCollider::Check_Collision_AABB(Engine::CCollider* targetCollider)
{
	return false;
}

Engine::CComponent * Engine::CCollider::Creat(LPDIRECT3DDEVICE9 pDevice)
{
	CCollider* pInstance = new CCollider(pDevice);
	return pInstance;
}

Engine::CComponent * Engine::CCollider::Clone()
{
	return new CCollider(*this);
}

void Engine::CCollider::Free()
{

	Engine::CComponent::Free();
}
