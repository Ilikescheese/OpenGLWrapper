 #pragma once
#include "wrapperPch.h"

//TODO: Make bindless, support more layouts etc
namespace OGL {
	class UBObj
	{
		static inline unsigned m_bindPointCounter = 0;
		GLuint m_bindingPoint,m_ubo;
	public:
		std::size_t std140Pad(std::size_t size); //Pad a number of bytes to a mult of 16
		//The number of floats in the datatype
		enum std140Types : int {
			vec1 = 1,
			vec2 = 2,
			vec3 = 4,
			vec4 = 4,
			mat2 = 4,
			mat3 = 9,
			mat4 = 16
		};
		GLuint getObject() const;
		unsigned getBindingPoint() const;
		const char *name = nullptr;
		std::vector<std140Types> block;
		void bind();
		void unbind();
		void destroy();
		//TODO: functionality for setting the entire block's data with one array of bytes
		//the "whereIndex" is what element of the block vector to target to get the memory offset for
		std::size_t getWhereOffset(unsigned idx);

		template<typename T>
		void setValue(unsigned whereIndex,T &value);

		//Create using a list of datatypes under the std140 layout
		void createStd140(const char *blockName, std::initializer_list<std140Types> blockContents);

		UBObj() = default;
	};

	template<typename T>
	inline void UBObj::setValue(unsigned whereIndex, T &value) {
		std::size_t offset = getWhereOffset(whereIndex);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(value), &value);
	}
}
