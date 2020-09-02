#pragma once
#include <glad/glad.h>
#include <initializer_list>
#include <vector>
class VAObj
{
	GLuint m_buffers[2]; // vbo ebo 
	GLuint m_vao;
	void m_setVertLayout(const std::initializer_list<size_t> &list) const;
public:
	void use() const;
	void destroy() const;
	VAObj(float *vertices, std::initializer_list<std::size_t> layout, GLenum storageType);
	VAObj(const float *vertices, const unsigned *indices, std::initializer_list<std::size_t> layout, GLenum storageType);
	VAObj(VAObj &) = delete;

};

