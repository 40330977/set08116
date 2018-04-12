#version 440

uniform vec2 scalel;//adjusts the frequency of the lattice
uniform vec2 threshold;//set threshold value
uniform vec3 surface;//surface colour applied

layout(location = 0) in vec3 diffusecolour;
layout(location = 1) in vec3 specularcolour;
layout(location = 2) in vec2 texcoord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main(){

float ss = fract(texcoord.s*scalel.s);
float tt = fract(texcoord.t*scalel.t);//fractional components give a value between 0 and 1

if((ss> threshold.s) && (tt> threshold.t)){
discard;}//compared with set threshold to determine if it should be discarded


vec3 frag = surface * diffusecolour + specularcolour;//calculate colour

colour = vec4(frag, 1.0);
}