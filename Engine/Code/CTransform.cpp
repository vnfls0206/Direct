#include "stdafx.h"
#include "CTransform.h"

// Ŭ���� �θ� �ڽİ� ������ �� �Ҹ��� ȣ�� ����\
// Ŭ���� 4�� �����ڿ� �� ����
// ����


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
	// ������Ÿ�� �ʱ�ȭ�κ�

	return S_OK;
}
HRESULT Engine::CTransform::Init_Transform_Clone()
{
	// Ŭ�� �ʱ�ȭ�κ�

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

	D3DXMatrixScaling(&matScale, m_vecScale.x, m_vecScale.y, m_vecScale.z);				// �� ����
	D3DXMatrixRotationX(&matRotX, m_vecRotation.x);										// �� ����
	D3DXMatrixRotationY(&matRotY, m_vecRotation.y);
	D3DXMatrixRotationZ(&matRotZ, m_vecRotation.z);
	D3DXMatrixTranslation(&matPos, m_vecPosition.x, m_vecPosition.y, m_vecPosition.z);	// �� ����

	D3DXMatrixIdentity(&m_matLocal);
	m_matLocal = matScale * (matRotX * matRotY * matRotZ) * matPos;

	if(m_pmatParent != nullptr)
		m_matLocal *= (*m_pmatParent);													// ��(��)
																						// ��(���̵���)
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

D3DXVECTOR3 Engine::CTransform::Get_Position()
{
	return m_vecPosition;
}

Engine::CTransform * Engine::CTransform::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::CTransform* pInstance = new CTransform(pGraphicDev);
	if (pInstance->Init_Transform_Proto()){
		MSG_BOX("Ʈ������ ������Ÿ�� �ʱ�ȭ�������߽��ϴ�");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

Engine::CTransform * Engine::CTransform::Clone()
{
	Engine::CTransform* pInstance = new CTransform(*this);
	if (pInstance->Init_Transform_Clone()) {
		MSG_BOX("Ʈ������ Ŭ�� �ʱ�ȭ�������߽��ϴ�");
		Engine::Safe_Release(pInstance);
	}
	return pInstance;
}

void Engine::CTransform::Free()
{
	Engine::CComponent::Free();
}


