#pragma once
#include <glad/glad.h>
#include <initializer_list>
#include <vector>

#include "VertConfig.h"
namespace OGL {
	class VAObj
	{
		inline static GLuint m_bindingPointCounter;
		GLuint m_bindingPoint;
		GLuint m_vao;
		GLuint m_buffers[2]; // vbo ebo 
		void m_setLayout(const std::initializer_list<VConf> &list);
		VAObj(unsigned setter); // Used by OGL::Initializer to set the binding point to zero

		void m_super();
	public:
		enum bufNames {
			vbo, ebo
		};
		friend class Initializer;
		void use() const;
		void destroy() const;
		VAObj(std::vector<float> &vertices, std::initializer_list<VConf> layout);
		VAObj(std::vector<float> &vertices, std::vector<unsigned> &indices, std::initializer_list<VConf> layout);
		VAObj(VAObj &) = delete;
	};
}
