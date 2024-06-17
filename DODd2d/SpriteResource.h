#include <vector>
#include "SpriteGI.h"

struct ID2D1Bitmap;

namespace dod
{
	struct SpriteResource
	{
		SpriteResource(ID2D1Bitmap* bitmap) : bitmap(bitmap)
		{

		}

		ID2D1Bitmap* bitmap;
		std::vector<SpriteGI> infoVector;
	};
}