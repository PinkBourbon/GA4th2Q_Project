#pragma once
#include "RenderComponent.h"

namespace dod
{
	class RenderRect : public RenderComponent
	{
		friend class GIEngine;

	public:

		RenderRect(float topX, float topY, float bottomX, float bottomY, int layer) :
			_rectTopX(topX), _rectTopY(topY), _rectBottomX(bottomX), _rectBottomY(bottomY), _fillCheck(0), RenderComponent(eRenderType::RECT, layer)
		{

		}
		virtual ~RenderRect(){}

		void FillCheck() { _fillCheck = 1; }

	protected:
		float _rectTopX;
		float _rectTopY;
		float _rectBottomX;
		float _rectBottomY;
		int _fillCheck;
	};
}

