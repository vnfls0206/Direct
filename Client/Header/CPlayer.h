#ifndef CPlayer_h__
#define CPlayer_h__

#include "CGameObject.h"

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
class CCollider;
END

class CPlayer final :
	public Engine::CGameObject
{
public:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CPlayer(const CPlayer& rhs);
	virtual ~CPlayer() = default;

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialize_GameObject() override;
	virtual HRESULT Initialize_CloneObject();

	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;

public :
	static CGameObject * Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject * Clone() override;

private :
	// ������Ʈ ���
	Engine::CTransform* m_pTransform;
	Engine::CBuffer* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;
	Engine::CCollider* m_pCollider;

private :
	HRESULT Ready_Shader(const float& fTimeDelta);

private :
	POINT m_pCursor = { 0,0 };
	float m_fTimeAcc;
	
	unsigned int m_iMinIndex = 0;
	unsigned int m_iMaxIndex = 5;
	unsigned int m_iCurIndex = 0;

private :
	float	m_fMoveSpeed = 200.f;

protected :
	virtual void Free() override;
};



#endif