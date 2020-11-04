#pragma once
#include <string>
struct Image {
	unsigned char *data = nullptr;
	std::string name;
	int width, height,nChannels;
	Image() = default;
	Image(const char *path);
	void destroy();
};