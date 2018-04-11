#version 440

uniform vec2 scale;
uniform vec2 threshold;
uniform vec3 surface;

layout(location = 0) in vec3 diffusecolour;
layout(location = 1) in vec3 specularcolour;
layout(location = 2) in vec2 texcoord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main(){

float ss = fract(texcoord.s*scale.s);
float tt = fract(texcoord.t*scale.t);

if((ss> threshold.s) && (tt> threshold.t)){
discard;}

vec3 frag = surface * diffusecolour + specularcolour;

colour = vec4(frag, 1.0);
}