#pragma once
#include "RenderCmd.h"
namespace OGL {
	static inline void drawArrays(RenderCmd &cmd) {
		glDrawArrays(cmd.mode, cmd.begin, cmd.end);
	}
	static inline void drawElements(RenderCmd &cmd) {
		glDrawElements(cmd.mode, cmd.end, cmd.indicesType, nullptr);
	}
	static inline void drawElementsInstanced(RenderCmd &cmd) {
		glDrawElementsInstanced(cmd.mode, cmd.end, cmd.indicesType, nullptr, cmd.instCount);
	}
}