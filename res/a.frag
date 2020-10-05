#version 450 core
#extension GL_ARB_bindless_texture : require
out vec4 imagery;
in vec2 uv;

layout(bindless_sampler) uniform sampler2DArray tex;
//the bindless sampler's sampler2Ds collect within the following array of 10
uniform int layer;
void main(){
	imagery = texture(tex,vec3(uv,layer));
}