#pragma once
#include "Texture2D.h"
#include "Image.h"
#include <vector>
namespace OGL {
	class Texture2DArray : public Texture2D
	{
		void m_setup(bool mips, unsigned numLayers);
		std::vector<Image> m_images;
		//unsigned m_calcRequiredLayers();
	public:
		const unsigned layerW, layerH;
		unsigned layerCount = 0;

		void add(Image &image, unsigned xOffset = 0, unsigned yOffset = 0, unsigned z = 0);
		//Texture2DArray(std::vector<Image> images, unsigned width, unsigned height, unsigned depth = 32, bool useMips = true);
		Texture2DArray(unsigned layerW, unsigned layerH, unsigned depth = 32, bool useMips = true);
		void destroy() const;
	};
}

