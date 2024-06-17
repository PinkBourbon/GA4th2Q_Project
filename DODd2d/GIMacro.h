#pragma once
namespace dod
{
	template<typename T>
	inline void
		SafeRelease(T** ppIToRelease)
	{
		if (*ppIToRelease != NULL)
		{
			(*ppIToRelease)->Release();

			(*ppIToRelease) = NULL;
		}
	}

	// #ifndef Assert
	// #if defined( DEBUG ) || defined( _DEBUG )
	// #define Assert(b) if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}
	// #else
	// #define Assert(b)
	// #endif //DEBUG || _DEBUG
	//#endif

#ifndef HINST_THISCOMPONENT
	EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
}