#include "stdafx.h"
#include "CComponent.h"


Engine::CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{

}

LPDIRECT3DDEVICE9 Engine::CComponent::Get_Graphic_Device()
{
	return m_pGraphic_Device;

}


Engine::CComponent::CComponent(const CComponent & rhs)
	: m_pGraphic_Device(rhs.m_pGraphic_Device)
{
	AddRef();
}

void Engine::CComponent::Free()
{

}
