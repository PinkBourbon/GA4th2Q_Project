#pragma once
#include "RenderComponent.h"

namespace dod
{
	class RenderLine : public RenderComponent
	{
		friend class GIEngine;

	public:
		RenderLine(float posX1, float posY1, float posX2, float posY2, int layer) :
			_linePoxX1(posX1), _linePoxY1(posY1), _linePoxX2(posX2), _linePoxY2(posY2), RenderComponent(eRenderType::LINE, layer)
		{

		}
		virtual ~RenderLine(){}

	protected:
		float _linePoxX1;
		float _linePoxY1;
		float _linePoxX2;
		float _linePoxY2;
	};
}


