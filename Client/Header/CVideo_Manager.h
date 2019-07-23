#ifndef CVideo_Manager_h__
#define CVideo_Manager_h__

#include "CBase.h"

class CVideo_Manager final
	: public Engine::CBase
{
	DECLARE_SINGLETON(CVideo_Manager)

private :
	explicit CVideo_Manager() = default;
	virtual ~CVideo_Manager() = default;

public :
	void Ready_Video();
	void Play_Video();

private:
	HWND	m_hVideo;

public :
	virtual void Free() override;
};

#endif