#include "stdafx.h"
#include "CComponent.h"


Engine::CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{

}

Engine::CComponent::CComponent(const CComponent & rhs)
	: m_pGraphic_Device(rhs.m_pGraphic_Device)
{
	AddRef();
}

void Engine::CComponent::Free()
{

}
