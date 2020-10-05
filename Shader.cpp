#include "Shader.h"
void OGL::Shader::m_check() {
	//TODO: add tesselation & geometry shader support 
	GLint target[3] = {
		GL_ACTIVE_PROGRAM,
		GL_VERTEX_SHADER,
		GL_FRAGMENT_SHADER
	};
	for (int i = 0; i < 3; i++) {
		GLint good;
		glGetProgramPipelineiv(target[i], GL_LINK_STATUS, &good);
		if (!good) {
			GLint bufLen;
			glGetProgramPipelineiv(target[i], GL_INFO_LOG_LENGTH, &bufLen);
			GLsizei logLen = bufLen;
			GLchar *log = nullptr;
			glGetProgramPipelineInfoLog(target[i], bufLen, &logLen, log);
			std::cerr << "OGL::Shader failure:" << log << '\n';
		}
	}
}

void OGL::Shader::use() const {
	glBindProgramPipeline(m_pipeline);
}

void OGL::Shader::attach(ShaderProg &vProg, ShaderProg &fProg) {
	glUseProgramStages(m_pipeline, GL_VERTEX_SHADER_BIT, vProg.object);
	glUseProgramStages(m_pipeline, GL_FRAGMENT_SHADER_BIT, fProg.object);
}

OGL::Shader::Shader() {
	glCreateProgramPipelines(1, &m_pipeline);
}

OGL::Shader::Shader(ShaderProg &vProg, ShaderProg &fProg) {
	glCreateProgramPipelines(1, &m_pipeline);
	attach(vProg, fProg);
}
