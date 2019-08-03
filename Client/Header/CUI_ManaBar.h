#ifndef CUI_ManaBar_h__
#define CUI_ManaBar_h__

#include "CGameObject.h"

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
END

class CUI_ManaBar final :
	public Engine::CGameObject
{
public:
	explicit CUI_ManaBar(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CUI_ManaBar(const CUI_ManaBar& rhs);
	virtual ~CUI_ManaBar() = default;

	// CGameObject��(��) ���� ��ӵ�
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
	// ������Ʈ ���
	Engine::CTransform* m_pTransform;
	Engine::CBuffer* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;

private:
	HRESULT Ready_Shader(const float& fTimeDelta);



protected:
	virtual void Free() override;

private:
	float					m_fTimeAcc;
	float*					m_fPlayerMana;
public:
	void					Get_PlayMana(float* Mana);

};

#endif