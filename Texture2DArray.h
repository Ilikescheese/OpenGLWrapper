#pragma once
#include "Texture2D.h"
#include "Image.h"
#include <vector>
namespace OGL {
	class Texture2DArray : public Texture2D
	{
	public:
		void add(Image image);
		Texture2DArray(std::vector<Image> images, unsigned layerW, unsigned layerH, bool useMips = true);
	};
}

