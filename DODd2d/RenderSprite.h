#pragma once
#include "RenderComponent.h"
#include "SpriteGI.h"
#include "Id2d.h"
#include "ImageData.h"
#include <vector>


namespace dod
{
	class RenderSprite : public RenderComponent
	{
		friend class GIEngine;

	public:
		/// <summary>
		/// 이미지데이터 벡터를 만들고 푸쉬백 함수를 만들어 일정횟수 푸쉬 백한다(푸쉬백후 데이터 관리...몰?루)
		/// </summary>
		/// <param name="posX">중앙 X 좌표</param>
		/// <param name="posY">중앙 Y 좌표</param>
		/// <param name="layer">그림 레이어 (0이 가장 아래)</param>
		RenderSprite(float posX, float posY, int layer) :
			RenderComponent(eRenderType::SPRITE, layer),
			_posX(posX), _posY(posY), _imageDataIndex(0)
		{

		}
		~RenderSprite() {}

		int PushBackImageDataVector(std::wstring imagePath, double frameTime = 0.0333)
		{
			ImageData imageData(imagePath, frameTime);
			int imageDataIndex = (int)(_imageDataVector.size());
			_imageDataVector.push_back(imageData);
			return imageDataIndex;
		}

		void SetImageIndex(int imageDataIndex)
		{
			_imageDataIndex = imageDataIndex;
		}

		void ChangeLayer(int layer)
		{
			_layer = layer;
		}

		void ChangeCurrentAnimationIndex(int animationIndex)
		{
			_imageDataVector[_imageDataIndex].animationIndex = animationIndex;
		}

	protected:
		std::vector<ImageData> _imageDataVector;
		int _imageDataIndex;

		/// <summary>
		/// 이건 언제 바꿀려고 하는겁니까?
		/// </summary>

		// 그려질 이미지의 중앙 위치
		float _posX;
		float _posY;
	};
}
