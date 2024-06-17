#pragma once
#include <string>
#include "IComponent.h"

/// <summary>
/// 모든 객체가 가질 예정
/// </summary>
namespace dod
{
	enum class eRenderType
	{
		NONE,
		CIRCLE,
		RECT,
		LINE,
		TEXT,
		SPRITE
	};

	struct Transform;
	struct Matrix3x3;

	class RenderComponent : public IComponent
	{
		friend class GIEngine;

	public:
		RenderComponent(eRenderType eType, int layer) : IComponent(eComponentType::Render), _type(eType), _layer(layer), _ptransform(nullptr) {}
		virtual ~RenderComponent() = 0 {}

		eRenderType GetRendertype()
		{
			return _type;
		}

		int GetLayerNumber()
		{
			return _layer;
		}

	public:
		void SetTransform(Transform* ptransform) { _ptransform = ptransform; }

	protected:
		Transform* _ptransform;
		eRenderType _type;
		int _layer;
		//std::array<int,3> layerlist;
	};
}