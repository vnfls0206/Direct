#include "stdafx.h"
#include "CSound_Manager.h"

IMPLEMENT_SINGLETON(CSound_Manager)

CSound_Manager::CSound_Manager()
{
	Initialize();
}


void CSound_Manager::Initialize()
{
	FMOD_System_Create(&m_pSystem);	// 시스템 할당
	FMOD_System_Init(m_pSystem, eCount, FMOD_INIT_NORMAL, nullptr); // 시스템 초기화
	LoadSoundFile();
}

void CSound_Manager::Update()
{
	FMOD_System_Update(m_pSystem);
}

void CSound_Manager::PlaySound(const TCHAR* pSoundKey, CHANNEL_ID eID)
{
	auto iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
		[&](auto& MyPair)
	{
		return !lstrcmp(pSoundKey, MyPair.first);
	});

	if (m_MapSound.end() == iter_find)
	{
		MessageBox(nullptr, L"Not Found Sound!", L"Error!", MB_OK);
		return;
	}

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter_find->second, FALSE, &m_pChannel[eID]);
}

void CSound_Manager::PlayBGM(const TCHAR * pSoundKey)
{
	auto iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
		[&](auto& MyPair)
	{
		return !lstrcmp(pSoundKey, MyPair.first);
	});

	if (m_MapSound.end() == iter_find)
	{
		MessageBox(nullptr, L"Not Found Sound!", L"Error!", MB_OK);
		return;
	}

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter_find->second, FALSE, &m_pChannel[eBGM]);
	FMOD_Channel_SetMode(m_pChannel[eBGM], FMOD_LOOP_NORMAL);
}

void CSound_Manager::StopSound(CHANNEL_ID eID)
{
	FMOD_Channel_Stop(m_pChannel[eID]);
}

void CSound_Manager::StopAll()
{
	for (int i = 0; i < eCount; ++i)
		FMOD_Channel_Stop(m_pChannel[i]);
}

void CSound_Manager::PauseSound(CHANNEL_ID eID, BOOL bPause/* = TRUE*/)
{
	FMOD_Channel_SetPaused(m_pChannel[eID], bPause);
}

void CSound_Manager::PauseAll(CHANNEL_ID eID, BOOL bPause/* = TRUE*/)
{
	for (int i = 0; i < eCount; ++i)
		FMOD_Channel_SetPaused(m_pChannel[i], bPause);
}

void CSound_Manager::Add_Playlist_In_Queue(const TCHAR * pSoundKey, CHANNEL_ID eID)
{
	if ((pSoundKey == nullptr) || !lstrcmp(pSoundKey, L""))
	{
		MSG_BOX("사운드 키의 값이 nullptr이거나 비어있습니다.");
		return;
	}

	m_quePlaylist.emplace(pSoundKey, eID);
}

void CSound_Manager::Play_Sound_In_Queue()
{
	while (!m_quePlaylist.empty())
	{
		PlaySound(m_quePlaylist.front().first, m_quePlaylist.front().second);
		m_quePlaylist.pop();
	}

}

void CSound_Manager::LoadSoundFile()
{
	_finddata_t	fd;

	long handle = _findfirst("../../Resource/Sound/*.*", &fd);
	int iResult = 0;

	if (0 == handle)
	{
		MessageBox(nullptr, L"Empty Sound folder!!", L"Error!", MB_OK);
		return;
	}

	while (-1 != iResult)
	{
		char szFullPath[128] = "../../Resource/Sound/";
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT res = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, nullptr, &pSound);

		if (FMOD_OK == res)
		{
			TCHAR* pSoundKey = new TCHAR[strlen(fd.name) + 1];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * strlen(fd.name) + 1);

			MultiByteToWideChar(CP_ACP, 0, fd.name, strlen(fd.name) + 1,
				pSoundKey, strlen(fd.name) + 1);

			m_MapSound.insert({ pSoundKey, pSound });
		}

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);

	FMOD_System_Update(m_pSystem);
}

void CSound_Manager::Free()
{
	ReleaseAll();
}

void CSound_Manager::ReleaseAll()
{
	for (auto& MyPair : m_MapSound)
	{
		delete[] MyPair.first;
		FMOD_Sound_Release(MyPair.second);	// 사운드 객체 해제
	}

	while (!m_quePlaylist.empty())
	{
		delete[] m_quePlaylist.front().first;
		m_quePlaylist.pop();
	}
	m_MapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}
