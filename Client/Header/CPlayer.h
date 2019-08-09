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
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize_GameObject() override;
	virtual HRESULT Initialize_CloneObject();

	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;

public :
	static CGameObject * Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject * Clone() override;

private :
	// 컴포넌트 목록
	Engine::CTransform* m_pTransform;
	Engine::CBuffer* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;
	Engine::CCollider* m_pCollider;


public:
	void Set_Dex_P(D3DXVECTOR3 m_dex);

public:
	void Play_Damage(float damage);
	void Play_Use_Skill(float ManaCost);

	float* Get_Play_Hp();
	float* Get_Play_Mana();

private :
	HRESULT Ready_Shader(const float& fTimeDelta);

private :
	D3DXVECTOR3 m_Dex_p = {0,0,0 };
	float m_fTimeAcc;
	float m_fHp;
	float m_fMana;
	unsigned int m_iMinIndex = 0;
	unsigned int m_iMaxIndex = 5;
	unsigned int m_iCurIndex = 0;

private :
	float	m_fMoveSpeed = 200.f;

protected :
	virtual void Free() override;
};



#endif