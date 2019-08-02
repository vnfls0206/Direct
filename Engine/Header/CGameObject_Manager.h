#ifndef CGameObject_Manager_h__
#define CGameObject_Manager_h__

#include "CBase.h"
#include "CGameObject.h"
#include "CLayer.h"

BEGIN(Engine)

class ENGINE_DLL CGameObject_Manager final
	: public Engine::CBase
{
	DECLARE_SINGLETON(CGameObject_Manager)

private :
	explicit CGameObject_Manager();
	virtual ~CGameObject_Manager() = default;






public :
	// ������ => ���� �󸶸�ŭ�� ������Ÿ�� ���������, ���̾� ��������� �Ҵ��س�������.
	void				Reserve_Proto_Layer_Array(const int iNumScene);	// �Ű����� : �� ����

	// ������Ÿ�� �� ������ �ִ±��	
	void				Insert_Prototype_GameObject_To_ProtoMap(int iSceneID,  
		const TCHAR* pProtoTag, Engine::CGameObject* pGameObject = nullptr);

	// ������Ÿ�� ������, �ߺ�Ű�� ã�� ���
	Engine::CGameObject* Find_GameObejct_In_ProtoMap(int iSceneID,  const TCHAR* pProtoTag);

	// �ش� �ε����� �ʿ� �ִ� ��ü���� ��� �������ִ� ��� => ���̾��, ������Ÿ�� ��� ��������...
	void				Release_Map_All_Object(int iSceneID);

	// ���̾��, ������Ʈ�� �����ִ� ���
	void				Update_Layers(int iSceneID, const float& fTimeDelta);

	// ���̾�� ������Ÿ�� ��ü�� �����ϴ� ���
	Engine::CGameObject* Copy_Proto_GameObject_To_Layer(int iProtoSceneID,  const TCHAR* pProtoObjectTag,
													int iLayerSceneID,  const TCHAR* pLayerObjectTag);

	//  ���̾ ã���ִ� ���
	Engine::CLayer*		Find_Layer(int iLayerSceneID, const TCHAR* pLayerObjectTag);

private :
	int												m_iSceneNum;			// ���� ���� ����
	typedef map<const TCHAR*, Engine::CGameObject*>	MAPPROTO;
	typedef map<const TCHAR*, Engine::CLayer*>		MAPLAYER;

	MAPPROTO*										m_mapProto;
	MAPLAYER*										m_mapLayer;

public :
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};

END
#endif