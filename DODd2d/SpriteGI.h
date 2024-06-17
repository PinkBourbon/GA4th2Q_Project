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
		// �ڸ� �̹����� ������ ������ ��ǥ
		float oriX;
		float oriY;

		// �ڸ� �̹����� �ʺ�� ����
		float width;
		float height;

	};
}
