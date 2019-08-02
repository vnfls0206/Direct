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
	// 예약기능 => 내가 얼마만큼의 프로토타입 저장공간과, 레이어 저장공간을 할당해놓기위함.
	void				Reserve_Proto_Layer_Array(const int iNumScene);	// 매개변수 : 씬 개수

	// 프로토타입 맵 변수에 넣는기능	
	void				Insert_Prototype_GameObject_To_ProtoMap(int iSceneID,  
		const TCHAR* pProtoTag, Engine::CGameObject* pGameObject = nullptr);

	// 프로토타입 내에서, 중복키를 찾는 기능
	Engine::CGameObject* Find_GameObejct_In_ProtoMap(int iSceneID,  const TCHAR* pProtoTag);

	// 해당 인덱스의 맵에 있는 객체들을 모두 삭제해주는 기능 => 레이어와, 프로토타입 모두 날려야함...
	void				Release_Map_All_Object(int iSceneID);

	// 레이어에서, 업데이트를 돌려주는 기능
	void				Update_Layers(int iSceneID, const float& fTimeDelta);

	// 레이어로 프로토타입 객체를 복사하는 기능
<<<<<<< HEAD
	Engine::CGameObject* Copy_Proto_GameObject_To_Layer(int iProtoSceneID,  const TCHAR* pProtoObjectTag,
=======
	Engine::CGameObject* Copy_Proto_GameObject_To_Layer(int iProtoSceneID,  const TCHAR* pProtoObjectTag, 
>>>>>>> master
													int iLayerSceneID,  const TCHAR* pLayerObjectTag);

	//  레이어를 찾아주는 기능
	Engine::CLayer*		Find_Layer(int iLayerSceneID, const TCHAR* pLayerObjectTag);

private :
	int												m_iSceneNum;			// 씬의 개수 저장
	typedef map<const TCHAR*, Engine::CGameObject*>	MAPPROTO;
	typedef map<const TCHAR*, Engine::CLayer*>		MAPLAYER;

	MAPPROTO*										m_mapProto;
	MAPLAYER*										m_mapLayer;

public :
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};

END
#endif