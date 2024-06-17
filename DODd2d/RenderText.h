#pragma once
#include "RenderComponent.h"


// _engine->DrawTextKNT(600, 200, L"«Ï¿ÃπŒ ¡¶¿€: %.2f", abcd);
namespace dod
{
	class RenderText : public RenderComponent
	{
		friend class GIEngine;

	public:
		RenderText(float posX, float posY, int layer) :
			_posX(posX), _posY(posY), _str(nullptr), _strLength(0), _strCapacity(0), RenderComponent(eRenderType::TEXT, layer)
		{

		}		
		virtual ~RenderText()
		{
			delete[] _str;
		}

		void SetString(const wchar_t* str, ...);

	protected:
		float _posX;
		float _posY;
		wchar_t* _str;
		int _strLength;
		int _strCapacity;
	};

}

