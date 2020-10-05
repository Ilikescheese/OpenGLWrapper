#pragma once
#include "NMShader.h"
#include "ShaderProg.h"
//Modular shader which implements program pipelines
namespace OGL {
	class Shader : public NMShader
	{
		GLuint m_pipeline;
		void m_check(); //check for link/compilation and output to log
	public:
		virtual void use() const override;
		void attach(ShaderProg & vProg,ShaderProg & fProg);

		Shader();
		Shader(ShaderProg &vProg, ShaderProg &fProg);
		Shader(Shader &) = delete;
	};
}
