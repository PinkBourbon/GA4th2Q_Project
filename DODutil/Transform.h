#pragma once
#include <math.h>
#include "Matrix3x3.h"
#include "Vector3.h"
#include "IComponent.h"

namespace dod
{
	struct Transform : public IComponent
	{
	public:
		Transform();
		virtual ~Transform();

		Matrix3x3 GetTranformMatrix();
		void SetParent(Transform* newParent);
		void independentFromParent();
		Transform* GetParant();

	public:
		Vector3 scale;		//x, y 축에 대한 스케일 값
		Vector3 position;	//x, y 좌표의 위치 값
		float rotation;		// 360분법 각도		
	private:
		Transform* _pParentTransform;
	};
}