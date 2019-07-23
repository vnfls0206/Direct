#include "stdafx.h"
#include "CGraphic_Device.h"

IMPLEMENT_SINGLETON(Engine::CGraphic_Device)

Engine::CGraphic_Device::CGraphic_Device()
	: m_pSDK(nullptr), m_pDevice(nullptr)
{
}


HRESULT Engine::CGraphic_Device::Intialize_CGraphic_Device(HWND hwnd, eWinMode eState, int iWINCX, int iWINCY , LPDIRECT3DDEVICE9* ppGraphicDevice)
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		devicecaps;
	ZeroMemory(&devicecaps, sizeof(D3DCAPS9));


	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &devicecaps)))
	{
		MSG_BOX("GetDeviceCaps Failed");
		return E_FAIL;
	}


	DWORD		vp;
	if (devicecaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//vp |= D3DCREATE_MULTITHREADED;


	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	SetParameters(d3dpp, eState, hwnd, iWINCX, iWINCY);

	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL
		, hwnd, vp, &d3dpp, &m_pDevice)))
	{
		MSG_BOX("CreateDevice Failed");
		return E_FAIL;
	}

	if (nullptr != ppGraphicDevice)
	{
		*ppGraphicDevice = m_pDevice;
		m_pDevice->AddRef();
	}

	return S_OK;
}
void Engine::CGraphic_Device::SetParameters(D3DPRESENT_PARAMETERS& d3dpp, eWinMode eState, HWND hwnd, int iWINCX, int iWINCY)
{
	d3dpp.BackBufferWidth = iWINCX;
	d3dpp.BackBufferHeight = iWINCY;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

	d3dpp.MultiSampleQuality = 0;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = TRUE;

	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = eState;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}


void Engine::CGraphic_Device::Free()
{
	unsigned long ulReftCnt = 0;

	if (ulReftCnt = Engine::Safe_Release(m_pSDK))
	{
		MSG_BOX("SDK를 해제하는데 실패하였습니다!");
	}

	if (ulReftCnt = Engine::Safe_Release(m_pDevice))
	{
		MSG_BOX("Device를 해제하는데 실패하였습니다!");
	}

	return;
}
