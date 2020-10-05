#pragma once

struct Image {
	unsigned char *data = nullptr;
	int width, height,nChannels;
	Image() = default;
	Image(const char *path);
	void destroy();
};