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
	D3DXMATRIX matView;		// �佺���̽� ���(�����)

private :
	// Ortho = ��������
	DESC_PROJ stProj;
	D3DXMATRIX matProj;		// �������

	float m_fZoomRatio = 1.f;
public :
	DESC_VIEW& Get_View_DESC();

	// Perspective - ��������
	// Field Of View		: ����ü�� ���� �Ʒ� ���̰�
	// Aspect ����			: ȭ���� ����, ����� ȭ���� ���� (����, �ܾƿ�)
	// Near
	// Far
	void Set_Camera_Zoom(float fRatio);
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
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};


END
#endif