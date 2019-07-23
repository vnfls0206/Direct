#include "stdafx.h"
#include "CKeyManager.h"

IMPLEMENT_SINGLETON(Engine::CKeyManager)

Engine::CKeyManager::CKeyManager()
{
	ZeroMemory(m_bKey, sizeof(m_bKey));
}


bool Engine::CKeyManager::KeyPressing(int iVKey)
{
	if (GetAsyncKeyState(iVKey) & 0x8000)
		return true;

	return false;
}

bool Engine::CKeyManager::KeyDown(int iVKey)
{
	if (!m_bKey[iVKey] && GetAsyncKeyState(iVKey) & 0x8000)
	{
		m_bKey[iVKey] = !m_bKey[iVKey];
		return true;
	}
	return false;
}

bool Engine::CKeyManager::KeyUp(int iVKey)
{
	if (m_bKey[iVKey] && !(GetAsyncKeyState(iVKey) & 0x8000))
	{
		m_bKey[iVKey] = !m_bKey[iVKey];
		return true;
	}

	return false;
}

void Engine::CKeyManager::Update()
{
	for (int i = 0; i < VIRTUAL_KEY; ++i)
	{
		if (!m_bKey[i] && GetAsyncKeyState(i) & 0x8000)
			m_bKey[i] = !m_bKey[i];
		else if (m_bKey[i] && !(GetAsyncKeyState(i) & 0x8000))
			m_bKey[i] = !m_bKey[i];
	}
}

void Engine::CKeyManager::Free()
{
}
