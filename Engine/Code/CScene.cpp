#include "stdafx.h"
#include "CScene.h"

Engine::CScene::CScene(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pDevice(pGraphic_Device)
{
}

LPDIRECT3DDEVICE9 Engine::CScene::Get_Graphic_Device()
{
	return m_pDevice;
}



