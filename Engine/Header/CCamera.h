#ifndef CCamera_h__
#define CCamera_h__

#include "CGameObject.h"

BEGIN(Engine)

class ENGINE_DLL CCamera
	: public Engine::CGameObject
{
protected :
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CCamera(const CCamera& rhs);
	virtual ~CCamera() = default;

private :
	DESC_VIEW stView;
	D3DXMATRIX matView;		// 뷰스페이스 행렬(뷰행렬)

private :
	// Ortho = 직교투영
	DESC_PROJ stProj;
	D3DXMATRIX matProj;		// 투영행렬
public :
	DESC_VIEW& Get_View_DESC() { return stView; }

	// Perspective - 원근투영
	// Field Of View		: 절두체의 위와 아래 사이각
	// Aspect 비율			: 화면의 비율, 출력할 화면의 비율 (줌인, 줌아웃)
	// Near
	// Far

protected:
	void Calculate_ViewSpaceMatrix();
	void Calculate_ProjectionSpaceMatrix();

protected :
	virtual void Initialize_View_Proj_Matrix(DESC_VIEW pDESC_VIEW, DESC_PROJ pDESC_PROJ);
	virtual void Calculate_View_Proj_Matrix();

protected:
	virtual HRESULT Initialize_GameObject() = 0;
public:
	virtual void Update_GameObject(const float& fTimeDelta) = 0;
	virtual void LastUpdate_GameObject(const float& fTimeDelta) = 0;
	virtual void Render_GameObject() = 0;

public:
	virtual CGameObject* Clone() = 0;

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};


END
#endif