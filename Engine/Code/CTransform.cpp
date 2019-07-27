#include "stdafx.h"
#include "CTransform.h"

// 클래스 부모 자식간 생성자 및 소멸자 호출 순서\
// 클래스 4대 생성자와 그 역할
// 복습


Engine::CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphic_Deivce)
	: Engine::CComponent(pGraphic_Deivce),
	 m_pmatParent(nullptr)
{
	D3DXMatrixIdentity(&m_matLocal);
}

Engine::CTransform::CTransform(const Engine::CTransform & rhs)
	: Engine::CComponent(rhs),
	m_pmatParent(nullptr)
{
	D3DXMatrixIdentity(&m_matLocal);
}


HRESULT Engine::CTransform::Init_Transform_Proto()
{
	// 프로토타입 초기화부분

	return S_OK;
}
HRESULT Engine::CTransform::Init_Transform_Clone()
{
	// 클론 초기화부분

	return S_OK;
}


void Engine::CTransform::Make_LocalSpace_Matrix()
{
	D3DXMatrixIdentity(&m_matLocal);

	D3DXMATRIX matScale, matRotX, matRotY, matRotZ, matPos;

	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotX);
	D3DXMatrixIdentity(&matRotY);
	D3DXMatrixIdentity(&matRotZ);
	D3DXMatrixIdentity(&matPos);

	D3DXMatrixScaling(&matScale, m_vecScale.x, m_vecScale.y, m_vecScale.z);				// 스 케일
	D3DXMatrixRotationX(&matRotX, m_vecRotation.x);										// 자 전축
	D3DXMatrixRotationY(&matRotY, m_vecRotation.y);
	D3DXMatrixRotationZ(&matRotZ, m_vecRotation.z);
	D3DXMatrixTranslation(&matPos, m_vecPosition.x, m_vecPosition.y, m_vecPosition.z);	// 이 동값

	D3DXMatrixIdentity(&m_matLocal);
	m_matLocal = matScale * (matRotX * matRotY * matRotZ) * matPos;

	if(m_pmatParent != nullptr)
		m_matLocal *= (*m_pmatParent);													// 공(전)
																						// 부(모이동값)
}



D3DXVECTOR3 Engine::CTransform::Get_Position()
{
	return m_vecPosition;
}

D3DXMATRIX*	Engine::CTransform::Get_m_matLocal()
{ 
	return &m_matLocal;
}

void Engine::CTransform::Set_Scale(D3DXVECTOR3 vScale)
{
	m_vecScale = vScale;
}

void Engine::CTransform::Set_Rotation(D3DXVECTOR3 vRot) {
	m_vecRotation = vRot;
}

void Engine::CTransform::Set_Position(D3DXVECTOR3 vPos) {
	m_vecPosition = vPos;
}


void Engine::CTransform::MoveToMouse(POINT MousePoint, float movespeed, const float& fDeltaTime)
{
	m_vecMousePosition = { (float)MousePoint.x ,(float)MousePoint.y, -5.0f };
	m_vecDist = m_vecMousePosition - m_vecPosition;

	if (D3DXVec3Length(&m_vecDist) > 2.5f)
	{
		D3DXVec3Normalize(&m_vecDist, &m_vecDist);
		m_vecPosition.x += m_vecDist.x * fDeltaTime * movespeed;
		m_vecPosition.y += m_vecDist.y * fDeltaTime * movespeed;
	}
}


D3DXVECTOR3	Engine::CTransform::Get_Scale() {
	D3DXVECTOR3 vScale;

	D3DXVECTOR3 vecRight, vecUp, vecLook;

	memcpy(&vecRight, &m_matLocal._11, sizeof(D3DXVECTOR3));
	memcpy(&vecUp, &m_matLocal._21, sizeof(D3DXVECTOR3));
	memcpy(&vecLook, &m_matLocal._31, sizeof(D3DXVECTOR3));

	vScale.x = D3DXVec3Length(&vecRight);
	vScale.y = D3DXVec3Length(&vecUp);
	vScale.z = D3DXVec3Length(&vecLook);

	// D3DXVec3TransformNormal(,);
	// D3DXVec3TransformCoord(,);

	return vScale;
}


Engine::CTransform * Engine::CTransform::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::CTransform* pInstance = new CTransform(pGraphicDev);
	if (pInstance->Init_Transform_Proto()){
		MSG_BOX("트랜스폼 프로토타입 초기화에실패했습니다");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

Engine::CTransform * Engine::CTransform::Clone()
{
	Engine::CTransform* pInstance = new CTransform(*this);
	if (pInstance->Init_Transform_Clone()) {
		MSG_BOX("트랜스폼 클론 초기화에실패했습니다");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

void Engine::CTransform::Free()
{
	Engine::CComponent::Free();
}


