#pragma once
#include <glad/glad.h>
#include <initializer_list>
#include <vector>
class VAObj
{
	void m_setVertLayout(const std::initializer_list<size_t> &list) const;
public:
	GLuint buffers[2]; // vbo ebo 
	GLuint vao;
	void use() const;
	void destroy() const;
	VAObj(float *vertices, std::initializer_list<std::size_t> layout);
	VAObj(const float *vertices, const unsigned *indices, std::initializer_list<std::size_t> layout);
	VAObj(VAObj &) = delete;

};

