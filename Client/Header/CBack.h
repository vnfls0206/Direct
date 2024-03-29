#ifndef CBack_h__
#define CBack_h__

#include "CGameObject.h"

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
END

class CBack final :
	public Engine::CGameObject
{
public:
	explicit CBack(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBack(const CBack& rhs);
	virtual ~CBack() = default;

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

private:
	HRESULT Ready_Shader(const float& fTimeDelta);

private:
	float m_fTimeAcc;

	unsigned int m_iMinIndex = 0;
	unsigned int m_iMaxIndex = 2;
	unsigned int m_iCurIndex = 0;

private:
	float	m_fMoveSpeed = 20.f;
};



#endif