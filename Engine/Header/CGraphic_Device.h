#ifndef CGraphic_Device_h__
#define CGraphic_Device_h__

#include "CBase.h"

BEGIN(Engine)

class ENGINE_DLL CGraphic_Device
	: public CBase
{
	DECLARE_SINGLETON(CGraphic_Device)

public :
	enum eWinMode {eFullMode=0, eWInMode};

private :
	explicit CGraphic_Device();
	virtual ~CGraphic_Device() = default;

public :
	HRESULT Intialize_CGraphic_Device(HWND hwnd, eWinMode eState, int iWINCX, int iWINCY, LPDIRECT3DDEVICE9* ppGraphicDevice);
	LPDIRECT3DDEVICE9 Get_Graphic_Device() { return m_pDevice; }

private :
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp, eWinMode eState, HWND hwnd, int iWINCX, int iWINCY);


private :
	LPDIRECT3D9 m_pSDK;
	LPDIRECT3DDEVICE9 m_pDevice;


public :
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};



END
#endif