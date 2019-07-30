#ifndef CUI_h__
#define CUI_h__

#include "CGameObject.h"

enum e_UiNum { Card1=0, Card2 , Card3, Card4, Card5, Card6, NumCount};

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
END

class CUI final:
	public Engine::CGameObject
{
public:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CUI(const CUI& rhs);
	virtual ~CUI()=default;

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
	Engine::CTransform* m_pTransform ;
	Engine::CBuffer* m_pBufferCom ;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;

private:
	HRESULT Ready_Shader(const float& fTimeDelta);

private:
	float m_fTimeAcc;

	unsigned int m_iMinIndex = 0;
	unsigned int m_iMaxIndex = 6;
	unsigned int m_iCurIndex = 0;

protected:
	virtual void Free() override;

private:
	Engine::CTransform*		m_pPlayerTransform;

public:
	void					Get_Player_Transform(Engine::CTransform* vTransform);
};

#endif