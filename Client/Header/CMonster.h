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
END

class CMonster  :
	public Engine::CGameObject
{
public:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphic_Device, MON_INFO m_mon_info);
	explicit CMonster(const CMonster& rhs, MON_INFO m_mon_info);
	virtual ~CMonster() = default;

public:
	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialize_GameObject() override;
	virtual HRESULT Initialize_CloneObject();

	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;

	bool Is_Can_Attack();
	eMonsterState Get_State();

public:
	static CGameObject * Create(LPDIRECT3DDEVICE9 pGraphic_Device, MON_INFO m_mon_info);
	virtual CGameObject * Clone() override;

private:
	// ������Ʈ ���
	Engine::CTransform* m_pTransform;
	Engine::CBuffer* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;

	Engine::CGameObject* pPlayer = nullptr;
	Engine::CTransform* Target_p;

	//���� ���� & ����
	MON_INFO m_Info;						//������ ����
	eMonsterAlignment m_Alignment = eGOOD;	//������ ����, Good(��)���� �ʱ�ȭ ���ش�
	eMonsterState m_Current_State = eLEFT_IDLE;	//������ ����, Idle(���)���� �ʱ�ȭ ���ش�
	CGameObject* Target = nullptr;
	bool IsCanAttack = false;

public:
	eMonsterState Get_Current_State();
	CGameObject* Get_Target();
	bool Get_Attack_Able();
	D3DXVECTOR3 Get_Dex_Position();

private:
	HRESULT Ready_Shader(const float& fTimeDelta);
	void Update_Current_State();

private:
	float m_fTimeAcc;

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

protected:
	float	m_fMoveSpeed = 80.f;
	float	m_fAttackDelay = 2.f;
};



#endif