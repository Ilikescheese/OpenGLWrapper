#include "VAObj.h"

void VAObj::m_setVertLayout(const std::initializer_list<size_t> &list) const {
	/*std::size_t stride = 0;
	for (auto i : list)
		stride += i;
	std::size_t offset = 0;
	unsigned cur = 0;
	for (const auto &attrib : list) {
		glVertexAttribPointer(cur, list.size(), GL_FLOAT, GL_FALSE, stride, (void *)offset);
		std::cout << "glVertexAttribPointer(" << cur
			glEnableVertexAttribArray(cur);
		offset += attrib;
		cur++;
	}*/
}

void VAObj::use() const {
	glBindVertexArray(m_vao);
}

void VAObj::destroy() const {
	glDeleteBuffers(2, m_buffers);
	glDeleteVertexArrays(1, &m_vao);
}

VAObj::VAObj(float *vertices, std::initializer_list<std::size_t> layout, GLenum storageType) {
	glCreateVertexArrays(1, &m_vao);
	use();
	glCreateBuffers(1, m_buffers); // Create vbo
	glVertexArrayVertexBuffer(m_vao, 0, m_buffers[0], 0, 3 * sizeof(float));
	glVertexArrayBindingDivisor(m_vao, 0, 0);
	glVertexArrayAttribBinding(m_vao, 0, 0);

	glEnableVertexArrayAttrib(m_vao, 0);
	glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(m_vao, )

		m_setVertLayout(layout);
}

VAObj::VAObj(const float *vertices, const unsigned *indices, std::initializer_list<std::size_t> layout, GLenum storageType = GL_STATIC_DRAW) {
	glCreateVertexArrays(1, &m_vao);
	glCreateBuffers(2, m_buffers);


	m_setVertLayout(layout);
}
