#ifndef Enemy_h__
#define Enemy_h__

#include "CGameObject.h"

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
class CCollider;
END

class Enemy final :
	public Engine::CGameObject
{
public:
	explicit Enemy(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit Enemy(const Enemy& rhs);
	virtual ~Enemy() = default;

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize_GameObject() override;
	virtual HRESULT Initialize_CloneObject();

	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;

public:
	static CGameObject * Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject * Clone() override;

private:
	// 컴포넌트 목록
	Engine::CTransform* m_pTransform;
	Engine::CBuffer* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;
	Engine::CCollider* m_pCollider;

private:
	HRESULT Ready_Shader(const float& fTimeDelta);

private:
	POINT m_pCursor = { 200,180 };
	float m_fTimeAcc;

	unsigned int m_iMinIndex = 0;
	unsigned int m_iMaxIndex = 2;
	unsigned int m_iCurIndex = 0;

private:
	float	m_fMoveSpeed = 200.f;
};



#endif