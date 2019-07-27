#ifndef CCollider_h__
#define CCollider_h__

#include "CComponent.h"

BEGIN(Engine)

class ENGINE_DLL CCollider final : public Engine::CComponent
{
private:
	explicit CCollider(LPDIRECT3DDEVICE9 pDevice);
	explicit CCollider(const CCollider& rhs);
	virtual ~CCollider() = default;

private:
	D3DXVECTOR3 Center;			//콜라이더 중앙의 위치벡터
	D3DXVECTOR3 Axis[3];		//콜라이더 x y z축의 단위벡터
	D3DXVECTOR3 Extent;			//(vecMin + vecMax) / 2 의 값
	D3DXVECTOR3 vecMin, vecMax;

public:
	void Initialize_Collider(D3DXVECTOR3* p_vecPos, DWORD dwVertexNum, DWORD dwFVF);	//복사된 콜라이더 객체는 비어있음으로 게임오브젝트에서 반드시 초기화를 해줄 것
	void Set_ColliderPos(D3DXVECTOR3* p_vecPos, DWORD dwVertexNum, DWORD dwFVF);
	bool Check_Collision_OBB(Engine::CCollider* targetCollider);				//obb충돌 판정
	bool Check_Collision_AABB(Engine::CCollider* targetCollider);				//aabb충돌 판정

public:
	static CComponent* Creat(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent* Clone() override;
	virtual void Free() override;

};

END
#endif

