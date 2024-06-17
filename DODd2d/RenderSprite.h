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
		/// �̹��������� ���͸� ����� Ǫ���� �Լ��� ����� ����Ƚ�� Ǫ�� ���Ѵ�(Ǫ������ ������ ����...��?��)
		/// </summary>
		/// <param name="posX">�߾� X ��ǥ</param>
		/// <param name="posY">�߾� Y ��ǥ</param>
		/// <param name="layer">�׸� ���̾� (0�� ���� �Ʒ�)</param>
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
		/// �̰� ���� �ٲܷ��� �ϴ°̴ϱ�?
		/// </summary>

		// �׷��� �̹����� �߾� ��ġ
		float _posX;
		float _posY;
	};
}
