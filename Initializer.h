#pragma once
#include "VAObj.h"

//Sets default values for abstracted objects *** Create this before anything else ***
//TODO: GL state object
namespace OGL {
	class Initializer
	{
	public:
		Initializer() {
			VAObj(0);
		}
	};
}

