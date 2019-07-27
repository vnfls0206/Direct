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
	D3DXMATRIX					m_matLocal;				// 자기자신의 행렬
	D3DXMATRIX*					m_pmatParent;			// 부모의 행렬 

	D3DXVECTOR3					m_vecScale;
	D3DXVECTOR3					m_vecRotation;
	D3DXVECTOR3					m_vecPosition;
	D3DXVECTOR3					m_vecMousePosition;		//마우스의 위치벡터
	D3DXVECTOR3					m_vecDist;				//마우스-플레이어의 거리벡터

public :
	void						Set_Scale(D3DXVECTOR3 vScale)
	{
		//memcpy(&m_vecScale, &vScale, sizeof(m_vecScale));
		m_vecScale = vScale;
	}
	void						Set_Rotation(D3DXVECTOR3 vRot) {
		m_vecRotation = vRot;
	}
	void						Set_Position(D3DXVECTOR3 vPos) {
		m_vecPosition = vPos;
	}

	void						MoveToMouse(POINT MousePoint, float movespeed, const float& fDeltaTime); //마우스 좌표로 이동

public :
	D3DXVECTOR3					Get_Scale() {
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
	D3DXVECTOR3					Get_Position();
	// 각도?
	// 이동값?

public :
	static CTransform* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CTransform* Clone() override;
	virtual void Free() override;
};

END
#endif