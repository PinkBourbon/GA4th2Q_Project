#include "DefineGI.h"

namespace dod
{
	DefineGI::DefineGI():
		_spriteType(),
		_index(0),
		_width(0),
		_height(0),
		_color(0),
		_centerPosX(0),
		_centerPosY(0),
		_delayFrame(0)
	{

	}

	DefineGI::DefineGI(eSpriteType spriteType, int index, float width, float height, int color, float centerX, float centerY, int delayFrame)
		: _spriteType(spriteType),
		_index(index),
		_width(width),
		_height(height),
		_color(color),
		_centerPosX(centerX),
		_centerPosY(centerY),
		_delayFrame(delayFrame)
	{

	}

	DefineGI::~DefineGI()
	{

	}
}