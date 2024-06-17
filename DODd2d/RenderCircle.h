#pragma once
#include "RenderComponent.h"

namespace dod
{
	class RenderCircle : public RenderComponent
	{
		friend class GIEngine;

	public:
		RenderCircle(float r, int layer) :_circleR(r), RenderComponent(eRenderType::CIRCLE, layer)
		{
			
		}
		virtual ~RenderCircle(){}
		

	protected:
		float _circleR;
	};
}