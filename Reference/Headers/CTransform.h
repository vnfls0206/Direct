#ifndef CTransform_h__
#define CTransform_h__

#include "CComponent.h"

BEGIN(Engine)

class ENGINE_DLL CTransform final :
	public Engine::CComponent
{
private :
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphic_Deivce);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform() = default;

public :
	HRESULT						Init_Transform_Proto();
	HRESULT						Init_Transform_Clone();

public :
	void						Make_LocalSpace_Matrix();
public:
	D3DXMATRIX*					Get_m_matLocal() { return &m_matLocal; }
private :
	D3DXMATRIX					m_matLocal;				// �ڱ��ڽ��� ���
	D3DXMATRIX*					m_pmatParent;			// �θ��� ��� 

	D3DXVECTOR3					m_vecScale;
	D3DXVECTOR3					m_vecRotation;
	D3DXVECTOR3					m_vecPosition;
	D3DXVECTOR3					m_vecMousePosition;		//���콺�� ��ġ����
	D3DXVECTOR3					m_vecDist;				//���콺-�÷��̾��� �Ÿ�����

public :
	void						Set_Scale(D3DXVECTOR3 vScale)
	{
		//memcpy(&m_vecScale, &vScale, sizeof(m_vecScale));
		D3DXVECTOR3 vecScale;
		m_vecScale = vScale;
		memcpy(&vecScale, &m_matLocal._11, sizeof(vecScale));
		D3DXVec3Normalize(&vecScale, &vecScale);
		vecScale * D3DXVec3Length(&vScale);
		memcpy(&m_matLocal._11, &vecScale, sizeof(vecScale));

		memcpy(&vecScale, &m_matLocal._21, sizeof(vecScale));
		D3DXVec3Normalize(&vecScale, &vecScale);
		vecScale * D3DXVec3Length(&vScale);
		memcpy(&m_matLocal._21, &vecScale, sizeof(vecScale));

		memcpy(&vecScale, &m_matLocal._31, sizeof(vecScale));
		D3DXVec3Normalize(&vecScale, &vecScale);
		vecScale * D3DXVec3Length(&vScale);
		memcpy(&m_matLocal._31, &vecScale, sizeof(vecScale));


	}
	void						Set_Rotation(D3DXVECTOR3 vRot) {
		m_vecRotation = vRot;
		//D3DXMatrixRotationX(&m_matLocal, m_vecRotation.x);
		//D3DXMatrixRotationY(&m_matLocal, m_vecRotation.y);
		//D3DXMatrixRotationZ(&m_matLocal, m_vecRotation.z);
	}
	void						Set_Position(D3DXVECTOR3 vPos) {
		m_vecPosition = vPos;
		memcpy(&m_matLocal._41, &m_vecPosition, sizeof(m_vecPosition));
	}

	void						MoveToMouse(POINT MousePoint, float movespeed, const float& fDeltaTime); //���콺 ��ǥ�� �̵�

public :
	D3DXVECTOR3					Get_Scale() {
		/*D3DXVECTOR3 vScale;
		
		D3DXVECTOR3 vecRight, vecUp, vecLook;

		memcpy(&vecRight, &m_matLocal._11, sizeof(D3DXVECTOR3));
		memcpy(&vecUp, &m_matLocal._21, sizeof(D3DXVECTOR3));
		memcpy(&vecLook, &m_matLocal._31, sizeof(D3DXVECTOR3));

		vScale.x = D3DXVec3Length(&vecRight);
		vScale.y = D3DXVec3Length(&vecUp);
		vScale.z = D3DXVec3Length(&vecLook);

		// D3DXVec3TransformNormal(,);
		// D3DXVec3TransformCoord(,);

		return vScale;*/
		return m_vecScale;
	}
	D3DXVECTOR3					Get_Position();
	// ����?
	// �̵���?

public :
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CTransform* Clone() override;
	virtual void Free() override;
};

END
#endif