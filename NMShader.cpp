#include "NMShader.h"
#include "loadFile.h"

void OGL::NMShader::m_compile(GLuint shader) {
	glCompileShader(shader);

	//Shader compilation checks
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		int logSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		GLsizei length = logSize;
		GLchar *log = new GLchar[logSize];
		glGetShaderInfoLog(status, logSize, &length , log);
		std::cerr << "GL shader compilation failure:" << log << '\n';
		delete[] log;
	}
}

void OGL::NMShader::use() const {
	glUseProgram(m_program);
}

void OGL::NMShader::build(const char *vSource, const char *fSource) {
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vert, 1, &vSource, nullptr);
	m_compile(vert);
	glShaderSource(frag, 1, &fSource, nullptr);
	m_compile(frag);
	m_program = glCreateProgram();
	glAttachShader(m_program, vert);
	glAttachShader(m_program, frag);
	glLinkProgram(m_program);

	//Program linkage checking
	GLint status;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (!status) {
		int logSize;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logSize);
		GLchar *log = new GLchar[logSize];
		glGetShaderInfoLog(status, logSize, static_cast<GLsizei*>(&logSize), log);
		std::cerr << "GL program linkage failure:" << log << '\n';
		delete[] log;
	}

	glDeleteShader(vert);
	glDeleteShader(frag);
}

void OGL::NMShader::destroy() {
	glDeleteProgram(m_program);
}

void OGL::NMShader::setMat4(const char *parameter, const glm::mat4 &matrix) {
	glUniformMatrix4fv(glGetUniformLocation(m_program, parameter), 1, GL_FALSE, glm::value_ptr(matrix));
}

void OGL::NMShader::setVec2(const char *parameter, const glm::vec2 &vector) {
	glUniform2f(glGetUniformLocation(m_program,parameter),vector.x,vector.y);
}

void OGL::NMShader::setVec4(const char *parameter, const glm::vec4 &vector) {
	glUniform4f(glGetUniformLocation(m_program, parameter), vector.x, vector.y,vector.z,vector.w);
}

void OGL::NMShader::setInt(const char *parameter, const GLint &integer) {
	glUniform1i(glGetUniformLocation(m_program, parameter), integer);
}

void OGL::NMShader::setHandle(const char *parameter, const GLuint64 &value) {
	glUniformHandleui64ARB(glGetUniformLocation(m_program, parameter), value);
}

OGL::NMShader::NMShader(const char *vShadPath, const char *fShadPath) {
	build(loadFile(vShadPath).c_str(), loadFile(fShadPath).c_str());
}

OGL::NMShader::NMShader(NMShader &&rhs) noexcept {
	m_program = lhs.m_program;
}
