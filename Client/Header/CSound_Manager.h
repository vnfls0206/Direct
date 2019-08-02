#ifndef CSound_Manager_h__
#define CSound_Manager_h__

// FMOD
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

// 저수준 입출력
#include <io.h>
#include "Client_Include.h"
#include "CBase.h"

class CSound_Manager final :
	public Engine::CBase
{
public :
	DECLARE_SINGLETON(CSound_Manager)

	enum CHANNEL_ID { eBGM=0, ePlayer, eMonster, eCount};

private :
	explicit CSound_Manager();
	virtual ~CSound_Manager() = default;

	std::queue<pair<const TCHAR*, CHANNEL_ID>> m_quePlaylist;

public:
	void Update();
	void PlaySound(const TCHAR* pSoundKey, CHANNEL_ID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	void PauseSound(CHANNEL_ID eID, BOOL bPause = TRUE);
	void PauseAll(CHANNEL_ID eID, BOOL bPause = TRUE);
	void Add_Playlist_In_Queue(const TCHAR* pSoundKey, CHANNEL_ID eID);
	void Play_Sound_In_Queue();
private:
	void Initialize();
	void ReleaseAll();
	void LoadSoundFile();

private:
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound;	// 사운드 리소스 관리를 위한 map
	FMOD_SYSTEM*	m_pSystem;					// 사운드 재생 및 관리를 주도하는 시스템
	FMOD_CHANNEL*	m_pChannel[eCount];			// 사운드 재생을 위한 채널

public :
	virtual void Free() override;
};

#endif