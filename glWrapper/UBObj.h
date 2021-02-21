 #pragma once
#include "wrapperPch.h"
#include "NMShader.h"
//TODO: Make bindless, support more layouts etc
namespace OGL {
	class UBObj
	{
		static inline unsigned m_bindPointCounter = 0;
		GLuint m_bindingPoint,m_ubo;
		std::vector<GLint> m_offsets;
		std::unordered_map<std::string,GLint> m_block;
	public:
		GLuint getObject() const;
		unsigned getBindingPoint() const;
		std::string name;
		void bind();
		void unbind();
		void destroy();

		//TODO: functionality for setting the entire block's data with one array of bytes
		//Set a single value if you're setting a struct, set the whereIndex to the location of last variable in the struct
		template<typename T>
		void setValue(std::string uniformName, T value);

		void create(const NMShader &shader);

		UBObj(const std::string &blockName) : name(blockName) {};
	};

	template<typename T>
	inline void UBObj::setValue(std::string uniformName, T value) {
		auto it = m_block.find(uniformName);
		if(it != m_block.end())
			glBufferSubData(GL_UNIFORM_BUFFER, it->second, sizeof(value), &value);
		else
			std::cout << "Couldn't find the uniform named '" << uniformName << '\'' << " within the ubo block" << '\n';
	}
}
