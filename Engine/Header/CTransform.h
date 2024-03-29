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
	D3DXMATRIX*					Get_m_matLocal();
private :
	D3DXMATRIX					m_matLocal;				
	D3DXMATRIX*					m_pmatParent;			

	D3DXVECTOR3					m_vecScale;
	D3DXVECTOR3					m_vecRotation;
	D3DXVECTOR3					m_vecPosition;
	D3DXVECTOR3					m_DexPosition;
	D3DXVECTOR3					m_vecDist;				

public :
	void						set_Parent(D3DXMATRIX* Parent);
	void						Set_Scale(D3DXVECTOR3 vScale);
	void						Set_Rotation(D3DXVECTOR3 vRot);
	void						Set_Position(D3DXVECTOR3 vPos);
	POINT					    Set_ObjectPoint(D3DXVECTOR3 vPos, POINT MousePoint);
	void						MoveToPosition(D3DXVECTOR3 DexPosition, float movespeed, const float& fDeltaTime);

public :
	D3DXVECTOR3					Get_Scale();
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