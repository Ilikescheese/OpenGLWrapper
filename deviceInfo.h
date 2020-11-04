#pragma once
//TODO: fill out fields when wrapper is initialized
namespace OGL {
	static struct DeviceInfo {
		unsigned majVersion = 4;
		unsigned minVersion = 5;
		bool dsa = false;
		bool bindlessOperations = false;
		bool modularShaders = false;
		//etc..
	};
}