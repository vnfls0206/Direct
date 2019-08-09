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
	D3DXVECTOR3 Center = { 0.f,0.f,0.f };			//콜라이더 중앙의 위치벡터
	D3DXVECTOR3 Axis[3] = { { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f } };		//콜라이더 x y z축의 단위벡터
	D3DXVECTOR3 Extent = { 0.f,0.f,0.f };			//(vecMin + vecMax) / 2 의 값
	D3DXVECTOR3 vecMin = { 0.f,0.f,0.f }, vecMax = { 0.f,0.f,0.f };

	ID3DXLine* m_pLine = nullptr;

public:
	void Initialize_Collider(D3DXMATRIX* matLocal);	//복사된 콜라이더 객체는 비어있음으로 게임오브젝트에서 반드시 초기화를 해줄 것*
	void Set_ColliderPos(D3DXMATRIX* matLocal, float fScale = 1.f);
	bool Check_Collision_OBB(Engine::CCollider* targetCollider);				//obb충돌 판정
	bool Check_Collision_AABB(Engine::CCollider* targetCollider);				//aabb충돌 판정


	void Render_Collider(int A, int R, int G, int B);

public:
	static CComponent* Creat(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent* Clone() override;
	virtual void Free() override;



};

END
#endif

