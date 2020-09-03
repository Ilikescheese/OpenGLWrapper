#include "Shader.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::string OGL::Shader::m_loadFile(const char *path) {
	try {
		std::ifstream file(path, std::ios::in);
		file.exceptions(std::ios::failbit | std::ios::badbit);

		std::stringstream data;
		data << file.rdbuf();

		return data.str();
	}
	catch (const std::ios::failure &err) {
		std::cerr << path << " loading failure err:" << err.what() << '\n';
	}
	return "";
}

void OGL::Shader::m_compile(GLuint shader) {
	glCompileShader(shader);

	//glDebugMessageCallback covers this
	/*GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		int logSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
		GLsizei length = logSize;
		GLchar *log = new GLchar[logSize];
		glGetShaderInfoLog(status, logSize, &length , log);
		std::cerr << "GL shader compilation failure:" << log << '\n';
		delete[] log;
	}*/
}

void OGL::Shader::use() const {
	glUseProgram(m_program);
}

void OGL::Shader::build(const char *vSource, const char *fSource) {
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
	/*GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (!status) {
		int logSize;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
		GLchar *log = new GLchar[logSize];
		glGetShaderInfoLog(status, logSize, static_cast<GLsizei*>(&logSize), log);
		std::cerr << "GL program linkage failure:" << log << '\n';
		delete[] log;
	}*/
	glDeleteShader(vert);
	glDeleteShader(frag);
}

void OGL::Shader::destroy() {
	glDeleteProgram(m_program);
}

OGL::Shader::Shader(const char *vShadPath, const char *fShadPath) {
	build(m_loadFile(vShadPath).c_str(), m_loadFile(fShadPath).c_str());
}
