#include "VAObj.h"

void OGL::VAObj::m_setLayout(const std::initializer_list<VConf> &list) const {
	std::size_t stride = 0;
	for (auto i : list)
		stride += i.size;
	std::size_t offset = 0;
	glVertexArrayVertexBuffer(vao, 0, buffers[0], 0, stride);
	unsigned cur = 0;
	for (const auto &attrib : list) {
		glVertexArrayAttribFormat(vao, 0, attrib.componentCount, GL_FLOAT, GL_FALSE, offset);
		offset += attrib.size;
		cur++;
	}
}

void OGL::VAObj::use() const {
	glBindVertexArray(vao);
}

void OGL::VAObj::destroy() const {
	glDeleteBuffers(2, buffers);
	glDeleteVertexArrays(1, &vao);
}

OGL::VAObj::VAObj(std::vector<float> &vertices, std::initializer_list<OGL::VConf> layout) {
	glCreateVertexArrays(1, &vao);
	use();

	glCreateBuffers(1, &buffers[0]);
	glNamedBufferStorage(buffers[0], vertices.size() * sizeof(vertices[0]), vertices.data(), 0);

	m_setLayout(layout);
	glVertexArrayAttribBinding(vao, 0, 0);
	glEnableVertexArrayAttrib(vao, 0);
	//Binding points act as ids for dsa vbuffers
}