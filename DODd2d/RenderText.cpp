#include "RenderText.h"
#include <dwrite.h>

void dod::RenderText::SetString(const wchar_t* str, ...)
{
	va_list ap;
	va_start(ap, str);

	_strLength = _vscwprintf(str, ap) + 1;

	if (_strLength >_strCapacity)
	{


		delete[] _str;
		_str = new wchar_t[_strLength];

		_strCapacity = _strLength;
	}

	vswprintf_s(_str, _strLength, str, ap);

	va_end(ap);
}
