#include "wrapperPch.h"
#include "UBObj.h"

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

void OGL::UBObj::create(const NMShader &shader) {
	m_bindingPoint = m_bindPointCounter;
	m_bindPointCounter++;
	
	GLint uniformCount = 0;
	glGetActiveUniformBlockiv(shader.getObject(),m_ubo,GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,&uniformCount);

	GLint *indices = new GLint[uniformCount];
	glGetActiveUniformBlockiv(shader.getObject(), m_ubo, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,indices);

	GLint uniformNameSize = 0;
	glGetProgramiv(shader.getObject(),GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,&uniformNameSize);
	//Add up bytes in block & copy from heap allocated array to vector & check indices
	m_offsets.reserve(uniformCount);
	for (int i = 0; i < uniformCount; i++) {
		if (indices[i] == GL_INVALID_INDEX)
			std::cerr << "Invalid uniform name at index #" << indices[i] << '\n';
		GLint offset = 0;
		glGetActiveUniformsiv(shader.getObject(),1,reinterpret_cast<GLuint*>(indices[i]),GL_UNIFORM_OFFSET,&offset);
		m_offsets.push_back(offset);

		GLchar *curUniformName = nullptr;
		glGetActiveUniform(shader.getObject(),indices[i], uniformNameSize,nullptr,nullptr,nullptr,curUniformName);
		m_block.insert(std::make_pair(std::string(curUniformName),indices[i]));
	}

	glGenBuffers(1,&m_ubo);
	bind();
	glBufferData(GL_UNIFORM_BUFFER, m_offsets.front(),nullptr,GL_DYNAMIC_DRAW);
	unbind();
	delete[] indices;
}