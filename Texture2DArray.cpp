#include "Texture2DArray.h"
#include <iostream>
void OGL::Texture2DArray::add(Image image) {
	//TODO: 
	if (immutable) {
		std::cerr << "Cannot edit texture as the handle has been made resident..\n";
		return;
	}
	else {
		image.destroy();
	}
}

OGL::Texture2DArray::Texture2DArray(std::vector<Image> images,unsigned layerW,unsigned layerH, bool useMips) {
	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &m_object);
	glTextureParameteri(m_object, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_object, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(m_object, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(m_object, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureStorage3D(m_object,1, GL_RGBA8, layerW, layerH,images.size());

	for (int i = 0; i < images.size(); i++) {
		glTextureSubImage3D(m_object, 0, 0, 0, i, images[i].width, images[i].height, 1, GL_RGBA, GL_UNSIGNED_BYTE, images[i].data);
		images[i].destroy();
	}
	if (useMips)
		glGenerateTextureMipmap(m_object);
}
