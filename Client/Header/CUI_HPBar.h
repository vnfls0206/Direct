#ifndef CUI_HpBar_h__
#define CUI_HpBar_h__

#include "CGameObject.h"

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
END

class CUI_HpBar final :
	public Engine::CGameObject
{
public:
	explicit CUI_HpBar(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CUI_HpBar(const CUI_HpBar& rhs);
	virtual ~CUI_HpBar() = default;

	// CGameObject을(를) 통해 상속됨
public:
	virtual HRESULT Initialize_GameObject() override;
	virtual HRESULT Initialize_CloneObject();

public:
	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;

public:
	static CGameObject * Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	CGameObject * Clone() override;
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

protected:
	virtual void Free() override;

private:
	Engine::CTransform*		m_pObjectTransform;
	UINT*					m_fObjectHp;
public:
	void					Get_Object_Transform(Engine::CTransform* vTransform,UINT* HP);

};

#endif