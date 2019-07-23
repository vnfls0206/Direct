#include "stdafx.h"
#include "CBase.h"

Engine::CBase::CBase()
{


}

unsigned long Engine::CBase::AddRef(void)
{
	return ++ulRefCnt;
}

unsigned long Engine::CBase::Release(void)
{
	if (ulRefCnt == 0) {
		Free();
		return ulRefCnt;
	}
	else {
		return ulRefCnt--;
	}
}
