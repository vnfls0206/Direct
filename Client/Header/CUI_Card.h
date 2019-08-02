#ifndef CUI_Card_h__
#define CUI_Card_h__

#include "CGameObject.h"

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
END

class CUI_Card final:
	public Engine::CGameObject
{
public:
	explicit CUI_Card(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CUI_Card(const CUI_Card& rhs);
	virtual ~CUI_Card()=default;

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
	Engine::CTransform* m_pTransform ;
	Engine::CBuffer* m_pBufferCom ;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;

private:
	HRESULT Ready_Shader(const float& fTimeDelta);

private:
	float m_fTimeAcc;
	unsigned int m_iCard = 0;
	D3DXVECTOR3				m_vUiPosition;
	bool					m_bActivie = true;

protected:
	virtual void Free() override;
	
public:
	void					Set_CardInfo(D3DXVECTOR3 vec,int cardstate);
	void					Set_Activie(bool b);
};

#endif