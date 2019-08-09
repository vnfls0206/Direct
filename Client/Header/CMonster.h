#ifndef CMonster_h__
#define CMonster_h__

#include "CGameObject.h"
#include "CGameObject_Manager.h"

#include "Client_Include.h"


BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
class CCollider;
class CGameObject_Manager;
END

class CMonster  :
	public Engine::CGameObject
{
protected:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CMonster(const CMonster& rhs);
	virtual ~CMonster() = default;

protected:
	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialize_GameObject() = 0;
	virtual HRESULT Initialize_CloneObject() = 0;

public:
	virtual void Update_GameObject(const float & fTimeDelta) = 0;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) = 0;
	virtual void Render_GameObject() = 0;

public:
	virtual void Attack(const float& fTimeDelta) = 0;
	eMonsterState Get_Current_State();
	Engine::CGameObject* Get_Target();
	void Set_Target(Engine::CGameObject* pTarget);
	bool Get_Attack_Able();
	void Hit(UINT Damage);
	UINT Get_Hp();
	void Die();
	D3DXVECTOR3 Get_Dex_Position();


protected:
	HRESULT Ready_Shader(const float& fTimeDelta);
	void Update_Current_State();


public:
	virtual CGameObject * Clone() = 0;
	virtual void Free(); 

protected:
	Engine::CGameObject_Manager* m_pObjMgr;
	// ������Ʈ ���
	Engine::CTransform* m_pTransform;
	Engine::CBuffer* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;
	Engine::CCollider* m_pCollider;
	Engine::CCollider* m_pCollider_AttackRange;

	Engine::CTransform* m_pPlayer_Transform;
	Engine::CTransform* Target_p;


	//���� ���� & ����
	MON_INFO m_Info;						//������ ����
	eMonsterAlignment m_Alignment = eGOOD;	//������ ����, Good(��)���� �ʱ�ȭ ���ش�
	eMonsterState m_Current_State = eLEFT_IDLE;	//������ ����, Idle(���)���� �ʱ�ȭ ���ش�
	CGameObject* Target = nullptr;
	bool IsCanAttack = false;

protected:
	float m_fTimeAcc = 0.f;
	float m_fAttackTime = 0.f;					//공격모션과 공격타이밍의 싱크를 맞추는 용도
	float m_fMoveSpeed = 20.f;
	float	m_fAttackDelay = 2.f;

	


private:

	struct node
	{
		D3DXVECTOR3 position;
		unsigned int G, H;
		node *Parent_node;


	};
	bool Node_Check(Engine::CGameObject_Manager* GM, list<node*> checked_List, D3DXVECTOR3 t_Position);


	unsigned int m_iMinIndex = 0;
	unsigned int m_iMaxIndex = 2;
	unsigned int m_iCurIndex = 0;
	D3DXVECTOR3 Dex_Position;


};



#endif