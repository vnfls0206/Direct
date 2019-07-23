#ifndef CLayer_h__
#define CLayer_h__

#include "CBase.h"
#include "CGameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer
	: public Engine::CBase
{
private :
	explicit CLayer() = default;
	virtual ~CLayer() = default;

public :
	static CLayer* Create();

public :
	void Insert_GameObject_To_Layer(Engine::CGameObject* pGameObject);
	bool Find_OverLapped_GameObject_In_Layer(const Engine::CGameObject* pGameObejct);
	void Delete_GameObject_In_Layer(const int iObjectIndex);

public :
	Engine::CGameObject*			Get_GameObject_In_List(const int iIndex);

public :
	void Update_Layer(const float& fTimeDelta);

private :

	list<Engine::CGameObject*>		m_pList_GameObject;

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};


END
#endif