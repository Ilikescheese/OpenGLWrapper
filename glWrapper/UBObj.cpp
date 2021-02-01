#include "wrapperPch.h"
#include "UBObj.h"

std::size_t OGL::UBObj::std140Pad(std::size_t size) {
	// Go to the nearest chunk of 16
	size = (size|15)+1;
	return size;
}

void OGL::UBObj::bind() {
	//TODO: Bindless implementation
	glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
	//Connect GL_UNIFORM_BUFFER target to the binding point
	glBindBufferBase(GL_UNIFORM_BUFFER, m_bindingPoint, m_ubo);
}

void OGL::UBObj::unbind() {
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint OGL::UBObj::getObject() const {
	return m_ubo;
}

unsigned OGL::UBObj::getBindingPoint() const {
	return m_bindingPoint;
}

void OGL::UBObj::destroy() {
	glDeleteBuffers(1,&m_ubo);
}

std::size_t OGL::UBObj::getWhereOffset(unsigned idx) {
	//Add up bytes in the whole block
	float count = 0;
	for (int i = 0; i < idx; i++)
		count += block[i] * 4;
	return std140Pad(count);
}

void OGL::UBObj::createStd140(const char *blockName, std::initializer_list<std140Types> blockContents) {
	m_bindingPoint = m_bindPointCounter;
	m_bindPointCounter++;
	name = blockName;
	block = blockContents;

	//Add up bytes in the whole block
	std::size_t count = 0;
	for (auto &i : block)
		count += i * 4;
	std::size_t size = std140Pad(count);

	glGenBuffers(1,&m_ubo);
	bind();
	glBufferData(GL_UNIFORM_BUFFER,size,nullptr,GL_DYNAMIC_DRAW);
	unbind();
}