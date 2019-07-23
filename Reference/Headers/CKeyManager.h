#ifndef CKeyManager_h__
#define CKeyManager_h__

#include "CBase.h"

BEGIN(Engine)

#define VIRTUAL_KEY 0xff

class ENGINE_DLL CKeyManager final :
	public Engine::CBase
{
	DECLARE_SINGLETON(CKeyManager)

private :
	explicit CKeyManager();
	virtual ~CKeyManager() = default;

public:
	bool KeyPressing(int iVKey);
	bool KeyDown(int iVKey);
	bool KeyUp(int iVKey);
	void Update();

private:
	bool m_bKey[VIRTUAL_KEY];

public :
	virtual void Free() override;
};

END

#endif