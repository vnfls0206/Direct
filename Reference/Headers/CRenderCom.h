#ifndef CRenderCom_h__
#define CRenderCom_h__

#include "CComponent.h"
#include "CGameObject.h"

BEGIN(Engine)
class ENGINE_DLL CRenderCom final
	: public Engine::CComponent
{
public :
	enum eRender_Sequence { 
		eRender_1 = 0, eRender_2, eRender_3,
		eRender_4, eRender_5, eRender_6,
		eRender_7, eRender_8, eRender_9,
		eRender_10, eRender_Count };

private :
	explicit CRenderCom(LPDIRECT3DDEVICE9 pGraphic_Device);
	explicit CRenderCom(const CRenderCom& rhs);
	virtual ~CRenderCom() = default;

public :
	// 정해진 인덱스의 리스트에, 오브젝트를 넣는 함수입니다.
	void								Add_GameObject_To_List(eRender_Sequence eState, Engine::CGameObject* pGameObject = nullptr);
	// 렌더러에 있는 객체들을 렌더(그리기)합니다.
	void								Render_RenderCom();
private :
	Engine::CGameObject*				Check_GameObject_In_List_Overlapped(eRender_Sequence eState, Engine::CGameObject* pGameObject);




private :
	typedef list<CGameObject*>			LIST_OBJECT;
	LIST_OBJECT							m_pList_Object[eRender_Count];

private :
	void								Clear_List();

public:
	static CComponent* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CComponent* Clone() override;

public:
	virtual void Free() override;
};

END
#endif