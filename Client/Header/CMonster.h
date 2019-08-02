#ifndef CMonster_h__
#define CMonster_h__

#include "CGameObject.h"
#include "Client_Include.h"


BEGIN(Engine)
class CTransform;
class CBuffer;
class CTexture;
class CShader;
class CRenderCom;
END

class CMonster final :
	public Engine::CGameObject
{
public:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphic_Device, MON_INFO m_mon_info);
	explicit CMonster(const CMonster& rhs, MON_INFO m_mon_info);
	virtual ~CMonster() = default;

public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Initialize_GameObject() override;
	virtual HRESULT Initialize_CloneObject();

	virtual void Update_GameObject(const float & fTimeDelta) override;
	virtual void LastUpdate_GameObject(const float & fTimeDelta) override;
	virtual void Render_GameObject() override;

public:
	static CGameObject * Create(LPDIRECT3DDEVICE9 pGraphic_Device, MON_INFO m_mon_info);
	virtual CGameObject * Clone() override;

private:
	// 컴포넌트 목록
	Engine::CTransform* m_pTransform;
	Engine::CBuffer* m_pBufferCom;
	Engine::CTexture* m_pTextureCom;
	Engine::CShader* m_pShaderCom;
	Engine::CRenderCom* m_pRenderCom;

	Engine::CGameObject* pPlayer = nullptr;
	Engine::CTransform* m_pPlayer_Transform;

	//몬스터 정보 & 상태
	MON_INFO m_Info;						//몬스터의 정보
	eMonsterAlignment m_Alignment = eGOOD;	//몬스터의 성향, Good(선)으로 초기화 해준다
	eMonsterState m_Current_State = eLEFT_IDLE;	//몬스터의 상태, Idle(대기)으로 초기화 해준다
	CGameObject* Target = nullptr;
	bool IsCanAttack = false;

public:
	eMonsterState Get_Current_State();
	CGameObject* Get_Target();
	bool Get_Attack_Able();

private:
	HRESULT Ready_Shader(const float& fTimeDelta);
	void Update_Current_State();

private:
	float m_fTimeAcc;
	


	unsigned int m_iMinIndex = 0;
	unsigned int m_iMaxIndex = 2;
	unsigned int m_iCurIndex = 0;

private:
	float	m_fMoveSpeed = 20.f;
};



#endif