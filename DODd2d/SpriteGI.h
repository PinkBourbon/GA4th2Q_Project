#pragma once


namespace dod
{
	class SpriteGI
	{
		friend class GIEngine;
	public:
		SpriteGI(float oriX, float oriY, float width, float height)
			: oriX(oriX), oriY(oriY), width(width), height(height)
		{

		}

	private:
		// 자를 이미지의 왼쪽위 꼭지점 좌표
		float oriX;
		float oriY;

		// 자를 이미지의 너비와 높이
		float width;
		float height;

	};
}
