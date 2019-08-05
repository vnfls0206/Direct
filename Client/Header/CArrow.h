#ifndef CArrow_h__
#define CArrow_h__

#include "CGameObject.h"

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
class CCollider;
END

class CArrow 
	: public Engine::CGameObject
{
private:
	explicit CArrow(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CArrow(const CArrow& rhs);
	virtual ~CArrow() = default;

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize_GameObject() override;
	virtual HRESULT Initialize_CloneObject() ;
	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;

	void Set_Target(Engine::CGameObject* pTarget);
	void Set_Position(D3DXVECTOR3 vecPos);

	static Engine::CGameObject* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject * Clone() override;

private:
	Engine::CTransform* m_pTransform;
	Engine::CBuffer* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;
	Engine::CCollider* m_pCollider;
	CGameObject* m_pTarget = nullptr;

	float m_fMoveSpeed = 50.f;

public:
	virtual void Free();
};

#endif