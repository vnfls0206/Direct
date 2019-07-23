#ifndef CScene_Stage_h__
#define CScene_Stage_h__

#include "CScene.h"

class CScene_Stage final :
	public Engine::CScene
{
private:
	explicit CScene_Stage(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual ~CScene_Stage() = default;

	// CScene��(��) ���� ��ӵ�
private:
	virtual HRESULT Initialize_Scene() override;
public:
	// CScene��(��) ���� ��ӵ�
	virtual void Update_Scene(const float & fTimeDelta) override;
	virtual void Render_Scene() override;

public:
	static CScene_Stage* Create(LPDIRECT3DDEVICE9 pGraphic_Device);

public:
	virtual void Free() override;
};

#endif