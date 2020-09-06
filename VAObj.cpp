#include "VAObj.h"

/*
	TODO:If the same layout is provided, copy the binding point to other VAObj
	TODO:Templatize the data type used in vertices data
*/

void OGL::VAObj::m_setLayout(const std::initializer_list<VConf> &list) {
	std::size_t stride = 0;
	for (auto i : list)
		stride += i.size;
	std::size_t offset = 0;

	glVertexArrayVertexBuffer(m_vao, 0, m_buffers[bufNames::vbo], 0, stride);
	unsigned cur = 0;
	for (const auto &attrib : list) {
		glVertexArrayAttribFormat(m_vao, 0, attrib.componentCount, GL_FLOAT, GL_FALSE, offset);
		glVertexArrayAttribBinding(m_vao, cur, m_bindingPoint);
		offset += attrib.size;
		cur++;
	}
	glEnableVertexArrayAttrib(m_vao, m_bindingPoint);
}

OGL::VAObj::VAObj(unsigned setter) {
	m_bindingPoint = 0;
}

void OGL::VAObj::m_super() {
	m_bindingPoint = m_bindingPointCounter;
	m_bindingPointCounter++;
	glCreateVertexArrays(1, &m_vao);
	use();
}

void OGL::VAObj::use() const {
	glBindVertexArray(m_vao);
}

void OGL::VAObj::destroy() const {
	glDeleteBuffers(2, m_buffers);
	glDeleteVertexArrays(1, &m_vao);
}

OGL::VAObj::VAObj(std::vector<float> &vertices, std::initializer_list<OGL::VConf> layout) {
	m_super();
	//Create vbo and set storage
	glCreateBuffers(1, m_buffers);
	glNamedBufferStorage(m_buffers[bufNames::vbo], vertices.size() * sizeof(vertices[0]), vertices.data(), 0);

	m_setLayout(layout);
}

OGL::VAObj::VAObj(std::vector<float> &vertices, std::vector<unsigned> &indices, std::initializer_list<VConf> layout) {
	m_super();
	glCreateBuffers(2, m_buffers);
	glNamedBufferStorage(m_buffers[bufNames::vbo], vertices.size() * sizeof(vertices[0]), vertices.data(), 0);
	glNamedBufferStorage(m_buffers[bufNames::ebo], indices.size() * sizeof(indices[0]), indices.data(), 0);
	m_setLayout(layout);
}

