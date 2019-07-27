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
	D3DXVECTOR3 Center;			//�ݶ��̴� �߾��� ��ġ����
	D3DXVECTOR3 Axis[3];		//�ݶ��̴� x y z���� ��������
	D3DXVECTOR3 Extent;			//(vecMin + vecMax) / 2 �� ��
	D3DXVECTOR3 vecMin, vecMax;

public:
	void Initialize_Collider(D3DXVECTOR3* p_vecPos, DWORD dwVertexNum, DWORD dwFVF);	//����� �ݶ��̴� ��ü�� ����������� ���ӿ�����Ʈ���� �ݵ�� �ʱ�ȭ�� ���� ��
	void Set_ColliderPos(D3DXVECTOR3* p_vecPos, DWORD dwVertexNum, DWORD dwFVF);
	bool Check_Collision_OBB(Engine::CCollider* targetCollider);				//obb�浹 ����
	bool Check_Collision_AABB(Engine::CCollider* targetCollider);				//aabb�浹 ����

public:
	static CComponent* Creat(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent* Clone() override;
	virtual void Free() override;

};

END
#endif

