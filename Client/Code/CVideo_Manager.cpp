#include "stdafx.h"
#include "CVideo_Manager.h"

// 동영상 재생을 위한 헤더와 라이브러리를 포함
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

#include "Client_Include.h"

IMPLEMENT_SINGLETON(CVideo_Manager)

void CVideo_Manager::Ready_Video()
{
	// MCIWndCreate: 미디어 재생에 필요한 윈도우를 할당.
	m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR,
		L"../../Resource/Video/Logo.wmv");

	// 현재 윈도우의 위치를 설정
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, TRUE);
}
void CVideo_Manager::Play_Video()
{
	// 미디어 재생
	MCIWndPlay(m_hVideo);
}

void CVideo_Manager::Free()
{
	MCIWndClose(m_hVideo);
}
