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
	D3DXVECTOR3 Center = { 0.f,0.f,0.f };			//�ݶ��̴� �߾��� ��ġ����
	D3DXVECTOR3 Axis[3] = { { 0.f,0.f,0.f }, { 0.f,0.f,0.f }, { 0.f,0.f,0.f } };		//�ݶ��̴� x y z���� ��������
	D3DXVECTOR3 Extent = { 0.f,0.f,0.f };			//(vecMin + vecMax) / 2 �� ��
	D3DXVECTOR3 vecMin = { 0.f,0.f,0.f }, vecMax = { 0.f,0.f,0.f };

	ID3DXLine* m_pLine = nullptr;

public:
	void Initialize_Collider(D3DXMATRIX* matLocal);	//����� �ݶ��̴� ��ü�� ����������� ���ӿ�����Ʈ���� �ݵ�� �ʱ�ȭ�� ���� ��*
	void Set_ColliderPos(D3DXMATRIX* matLocal, float fScale = 1.f);
	bool Check_Collision_OBB(Engine::CCollider* targetCollider);				//obb�浹 ����
	bool Check_Collision_AABB(Engine::CCollider* targetCollider);				//aabb�浹 ����
	void ColliderScaleExpand();

	void Render_Collider(int A, int R, int G, int B);

public:
	static CComponent* Creat(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent* Clone() override;
	virtual void Free() override;



};

END
#endif

