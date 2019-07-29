#ifndef Engine_Macro_h__
#define Engine_Macro_h__

#define WINCX 800
#define WINCY 600

#define MSG_BOX(MESSAGE) MessageBox(0, TEXT(MESSAGE), TEXT("System Message"), MB_OK);

#define BEGIN(NAMESPACE) namespace NAMESPACE {
#define END }
#define USING(NAMESPACE) using namespace NAMESPACE;

#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif


#define DECLARE_SINGLETON(CLASSNAME)					\
private:												\
	static CLASSNAME* m_pInstance;						\
public:													\
	static CLASSNAME* GetInstance(void);				\
	static unsigned long DestroyInstance(void);			


#define IMPLEMENT_SINGLETON(CLASSNAME)											\
CLASSNAME* CLASSNAME::m_pInstance = nullptr;									\
CLASSNAME* CLASSNAME::GetInstance(void)											\
{																				\
	if (m_pInstance == nullptr) {												\
		m_pInstance = new CLASSNAME;											\
	}																			\
	return m_pInstance;															\
}																				\
unsigned long CLASSNAME::DestroyInstance(void)									\
{																				\
	unsigned long ulRefCnt = 0;													\
																				\
	if (m_pInstance != nullptr)													\
	{																			\
		ulRefCnt = m_pInstance->Release();										\
		if (ulRefCnt == 0)														\
			m_pInstance = nullptr;												\
	}																			\
	return ulRefCnt;															\
}





#endif