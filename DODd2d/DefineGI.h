#pragma once
/// <summary>
/// ��ü���� ���� �־�� ��(Abstract ���ϰ��� ����)
/// </summary>
namespace dod
{
	class DefineGI
	{
	public:
		enum class eSpriteType
		{
			eBWSpriteType,
			eSpritePos,
		};

		DefineGI();
		DefineGI(eSpriteType spriteType, int index, float width, float height, int color,
			float centerX, float centerY, int delayFrame);
		virtual ~DefineGI();


		// ��������ƮŸ��(�����)
		eSpriteType _spriteType;

		// ��ü
		int _index;

		// ��������Ʈ ����
		float _width;
		float _height;

		// ��
		int _color;

		// �ִϸ��̼� ����(�����)
		float _centerPosX;
		float _centerPosY;
		float _delayFrame;

	};
}