#include "stdafx.h"
#include "CVideo_Manager.h"

// ������ ����� ���� ����� ���̺귯���� ����
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

#include "Client_Include.h"

IMPLEMENT_SINGLETON(CVideo_Manager)

void CVideo_Manager::Ready_Video()
{
	// MCIWndCreate: �̵�� ����� �ʿ��� �����츦 �Ҵ�.
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,
		L"../../Resource/Video/Logo.wmv");

	// ���� �������� ��ġ�� ����
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, TRUE);
}
void CVideo_Manager::Play_Video()
{
	// �̵�� ���
	MCIWndPlay(m_hVideo);
}

void CVideo_Manager::Free()
{
	MCIWndClose(m_hVideo);
}
