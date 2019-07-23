#ifndef Engine_Function_h__
#define Engine_Function_h__


BEGIN(Engine)

template <typename T>
unsigned long Safe_Release(T& Obj) 
{
	unsigned long ulRefCnt = 0;
	if (Obj != nullptr)
	{
		ulRefCnt = Obj->Release();
		if (ulRefCnt == 0)
		{
			Obj = nullptr;
		}
	}
	return ulRefCnt;
}

template <typename T>
unsigned long Safe_Delete(T& Obj) 
{
	if (Obj != nullptr) {
		delete Obj;
		Obj = nullptr;
	}
}


template <typename T>
unsigned long Safe_Delete_Array(T& Obj) 
{
	if (Obj != nullptr) {
		delete[] Obj;
		Obj = nullptr;
	}
}

class CFinder_Tag
{
public:
	CFinder_Tag(const wchar_t* pTag) : m_pTag(pTag) {}
	~CFinder_Tag() = default;
public:
	template <typename T>
	bool operator ()  (T& Pair)
	{
		return !lstrcmp(Pair.first, m_pTag);
	}
private:
	const wchar_t* m_pTag;
};

END


#endif // ! Engine_Function_h__
