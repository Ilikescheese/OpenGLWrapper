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
	glBindVertexArray(vao);
}

void VAObj::destroy() const {
	glDeleteBuffers(2, buffers);
	glDeleteVertexArrays(1, &vao);
}

VAObj::VAObj(float *vertices, std::initializer_list<std::size_t> layout) {
	glCreateBuffers(1, buffers); // Create vbo only
	glNamedBufferStorage(buffers[0], sizeof(*vertices) / sizeof(float), vertices, 0);

	glCreateVertexArrays(1, &vao);

	glVertexArrayVertexBuffer(vao, 0, buffers[0], 0, sizeof(*vertices));
	//glVertexArrayBindingDivisor(vao, 0, 0);
	glVertexArrayAttribBinding(vao, 0, 0); // Bind format to binding point 0
	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE,0);
	//Binding points act as ids for dsa vbuffers
}

VAObj::VAObj(const float *vertices, const unsigned *indices, std::initializer_list<std::size_t> layout) {
}
