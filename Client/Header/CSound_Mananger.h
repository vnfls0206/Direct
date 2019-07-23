#ifndef CSound_Manager_h__
#define CSound_Manager_h__

// FMOD
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

// 저수준 입출력
#include <io.h>

#include "CBase.h"

class CSound_Mananger final :
	public Engine::CBase
{
public :
	DECLARE_SINGLETON(CSound_Mananger)

	enum CHANNEL_ID { eBGM=0, ePlayer, eCount};

private :
	explicit CSound_Mananger();
	virtual ~CSound_Mananger() = default;

public:
	void Update();
	void PlaySound(const TCHAR* pSoundKey, CHANNEL_ID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	void PauseSound(CHANNEL_ID eID, BOOL bPause = TRUE);
	void PauseAll(CHANNEL_ID eID, BOOL bPause = TRUE);

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