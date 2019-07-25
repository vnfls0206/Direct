#ifndef CGameObject_h__
#define CGameObject_h__

#include "CBase.h"
#include "CComponent.h"

BEGIN(Engine)
class CComponent_Manager;
class ENGINE_DLL CGameObject
	: public Engine::CBase
{
protected  :
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphic_Device);		// �⺻ ������
	explicit CGameObject(const CGameObject& rhs);					// ���� ������, new CGameObject(*this);
	virtual ~CGameObject() = default;								// �⺻ �Ҹ���

private :
	LPDIRECT3DDEVICE9 m_pDevice;
protected :
	LPDIRECT3DDEVICE9 Get_Graphic_Device() { return m_pDevice; }

protected :
	virtual HRESULT Initialize_GameObject() = 0;
public :
	virtual void Update_GameObject(const float& fTimeDelta) = 0;
	virtual void LastUpdate_GameObject(const float& fTimeDelta) = 0;
	virtual void Render_GameObject() = 0;


protected :
	typedef map<const TCHAR*, Engine::CComponent*>		MAPCOMPONENT;
	MAPCOMPONENT										m_mapComponent;
	CComponent_Manager*								m_pComponentMgr;			//���� ��ü�� ������Ʈ���� �߰��ϱ� ���� ������ü�� ���⿡ �߰��س���
public :
	Engine::CComponent*						Get_Component_In_Map(const TCHAR* pKey);

public :
	virtual CGameObject* Clone() = 0;

public :
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END

#endif