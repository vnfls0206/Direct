#ifndef CPlayer_h__
#define CPlayer_h__

#include "Client_Include.h"
#include "CGameObject.h"

BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
class CCollider;

class CGameObject_Manager;
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


public:
	void Set_Dex_P(D3DXVECTOR3 m_dex);

public:
	void Play_Damage(UINT damage);
	void Play_Use_Skill(float ManaCost);

	UINT* Get_Play_Hp();
	float* Get_Play_Mana();
	void Set_Target(Engine::CGameObject* pTarget);
	void Attack(const float& fTimeDelta);
	void Hit(UINT uiDamage);
	void Die();

private :
	HRESULT Ready_Shader(const float& fTimeDelta);

private :
	Engine::CGameObject_Manager* m_pObjMgr;
	POINT m_pCursor = { 0,0 };
	float m_fTimeAcc;
	float m_fAttackTime = 0.4f;  //���ݸ�� ��ũ�ο�
	PLAYER_INFO m_stInfo;
	eMonsterState m_Current_State = eUP_IDLE;
	Engine::CGameObject* m_pTarget = nullptr;
	unsigned int m_iMinIndex = 0;
	unsigned int m_iMaxIndex = 5;
	unsigned int m_iCurIndex = 0;

private :
	float	m_fMoveSpeed = 200.f;

protected :
	virtual void Free() override;
};



#endif