#version 440

uniform vec3 brick;//brick colour
uniform vec3 mortar;//mortar colour
uniform vec2 bsize;//brick size
uniform vec2 bpct;//brick percent

layout(location = 1) in vec2 modelcoordpos;
layout(location = 2) in float lightintensity;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main(){

vec3 fragcolour;
vec2 pos;
vec2 use;

pos = modelcoordpos/bsize;

if(fract(pos.y*0.5) > 0.5)//determines where in the pattern the position is
{
	pos.x += 0.5;//produces brick offset, remove + for deathstar like effect
}

pos = fract(pos);
use = step(pos, bpct);//generates the step function

fragcolour = mix(mortar, brick, use.x*use.y);//mix the brick and mortar colours based on the step function
fragcolour*=lightintensity;

colour = vec4(fragcolour, 1.0);
}
