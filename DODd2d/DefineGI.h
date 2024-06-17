#pragma once
/// <summary>
/// 객체마다 갖고 있어야 함(Abstract 파일과의 차이)
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


		// 스프라이트타입(예비용)
		eSpriteType _spriteType;

		// 객체
		int _index;

		// 스프라이트 정보
		float _width;
		float _height;

		// 색
		int _color;

		// 애니메이션 전용(예비용)
		float _centerPosX;
		float _centerPosY;
		float _delayFrame;

	};
}