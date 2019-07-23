#ifndef CStatic_Camera_h__
#define CStatic_Camera_h__

#include "CCamera.h"

BEGIN(Engine)
class CTransform;
END


class CStatic_Camera final
	: public Engine::CCamera
{
private :
	explicit CStatic_Camera(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CStatic_Camera(const CStatic_Camera& rhs);
	virtual ~CStatic_Camera() = default;


// CCamera을(를) 통해 상속됨
private :
	virtual HRESULT Initialize_GameObject() override;
	HRESULT Initialize_Camera_Matrix(Engine::DESC_VIEW tmpDESC_VIEW, Engine::DESC_PROJ tmpDESC_PROJ);

public :
	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;

public :
	static Engine::CGameObject* Create(LPDIRECT3DDEVICE9 pGraphic_Device 
		, Engine::DESC_VIEW tmpDESC_VIEW, Engine::DESC_PROJ tmpDESC_PROJ);
	virtual Engine::CGameObject* Clone() override;
	virtual void Free() override;

private :
	Engine::CTransform*		m_pPlayerTransform;
public :
	void					Get_Player_Transform(Engine::CTransform* vTransform);

};

#endif