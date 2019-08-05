#ifndef CSwordMonster_h__
#define CSwordMonster_h__

#include "CMonster.h"

class CSwordMonster :
	public CMonster

{
private:
	explicit CSwordMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CSwordMonster(const CSwordMonster& rhs);
	virtual ~CSwordMonster()= default;

	virtual HRESULT Initialize_GameObject() override;
	virtual HRESULT Initialize_CloneObject() override;
public:
	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;
public:
	virtual void Attack(const float& fTimeDelta) override;

public:
	static CGameObject * Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject * Clone() override;
};

#endif