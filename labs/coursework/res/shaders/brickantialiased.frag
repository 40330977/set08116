#version 440

uniform vec3 brick;//brick colour
uniform vec3 mortar;//mortar colour
uniform vec2 bsize;//brick size
uniform vec2 bpct;//brick percent
uniform vec2 mpct;//mortar percent

layout(location = 1) in vec2 modelcoordpos;
layout(location = 2) in float lightintensity;

// Outgoing colour
layout(location = 0) out vec4 colour;

vec2 integral(in vec2 x, in vec2 p, in vec2 notp) {    // integral function providing properly weighted average avoiding point sampling aliasing artefacts
vec2 use = ((floor(x)*(p))+ max(fract(x)-(notp), 0.0));
return use;
}

void main(){

vec3 fragcolour;
vec2 pos;
vec2 use;
vec2 fw;

pos = modelcoordpos/bsize;

if(fract(pos.y*0.5) > 0.5)//apply offset
{
	pos.x += 0.5;
}

fw = fwidth(pos);//calculate filter

use += (integral(pos+fw, bpct, mpct)-integral(pos, bpct, mpct))/fw;//integral of pulse over the filter width

fragcolour = mix(mortar, brick, use.x*use.y);
fragcolour*=lightintensity;

colour = vec4(fragcolour, 1.0);
}
