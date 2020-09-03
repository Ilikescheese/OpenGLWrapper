#pragma once
#include <glad/glad.h>
#include <initializer_list>
#include <vector>

#include "VertConfig.h"

namespace OGL {
	class VAObj
	{
		void m_setLayout(const std::initializer_list<VConf> &list) const;
	public:
		GLuint vao;
		GLuint buffers[2]; // vbo ebo 

		void use() const;
		void destroy() const;

		VAObj(std::vector<float> &vertices, std::initializer_list<VConf> layout);
		VAObj(std::vector<float> &vertices, std::vector<float> &indices, std::initializer_list<VConf> layout);
		VAObj(VAObj &) = delete;
	};
}
