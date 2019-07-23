#ifndef CSound_Manager_h__
#define CSound_Manager_h__

// FMOD
#include "fmod.h"
#pragma comment(lib, "fmodex_vc.lib")

// ������ �����
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
	map<const TCHAR*, FMOD_SOUND*>	m_MapSound;	// ���� ���ҽ� ������ ���� map
	FMOD_SYSTEM*	m_pSystem;					// ���� ��� �� ������ �ֵ��ϴ� �ý���
	FMOD_CHANNEL*	m_pChannel[eCount];			// ���� ����� ���� ä��

public :
	virtual void Free() override;
};

#endif