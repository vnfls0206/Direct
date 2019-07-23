#ifndef CBase_h__
#define CBase_h__

#include "Engine_Include.h"

BEGIN(Engine)

class ENGINE_DLL CBase abstract
{
protected :
	explicit CBase();
	virtual ~CBase() = default;

public :
	unsigned long AddRef(void);
	unsigned long Release(void);

private :
	unsigned long ulRefCnt = 0;

public :
	virtual void Free() = 0;
};

END

#endif