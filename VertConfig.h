#pragma once
#include <cstring>
namespace OGL {
	struct VConf {
		unsigned componentCount = 0;
		std::size_t size = 0;
		VConf(unsigned count) : size(sizeof(float) *count), componentCount(count) {};
		VConf() = default;
	};
}