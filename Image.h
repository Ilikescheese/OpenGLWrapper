#pragma once

struct Image {
	unsigned char *data = nullptr;
	int width, height,nChannels;
	const char *name = nullptr;
	Image() = default;
	Image(const char *path);
	void destroy();
};