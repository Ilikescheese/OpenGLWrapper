#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

Image::Image(const char *path){
	data = stbi_load(path, &width, &height, &nChannels, STBI_rgb_alpha);
	if (!data)
	std::cerr << "Failed to load image from path '" << path << "'!\n";
}

void Image::destroy() {
	if (data)
		stbi_image_free(data);
}
