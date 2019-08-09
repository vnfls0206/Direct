#ifndef CBowMonster_h__
#define CBowMonster_h__

#include "CMonster.h"
BEGIN(Engine)
class CGameObject_Manager;
END

class CBowMonster :
	public CMonster
{
private:
	explicit CBowMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBowMonster(const CBowMonster& rhs);
	virtual ~CBowMonster() = default;

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
