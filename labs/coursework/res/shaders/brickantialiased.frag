#version 440

uniform vec3 brick;
uniform vec3 mortar;
uniform vec2 bsize;
uniform vec2 bpct;
uniform vec2 mpct;

layout(location = 1) in vec2 modelcoordpos;
layout(location = 2) in float lightintensity;

// Outgoing colour
layout(location = 0) out vec4 colour;

#define integral(x, p, notp) ((floor(x)*(p))+ max(fract(x)-(notp), 0.0))

void main(){

vec3 fragcolour;
vec2 pos;
vec2 use;
vec2 fw;

pos = modelcoordpos/bsize;

if(fract(pos.y*0.5) > 0.5)
{
	pos.x += 0.5;
}

fw = fwidth(pos);

use = (Integral(pos+fw, bpct, mpct)-integral(pos, bpct, mpct))/fw;

fragcolour = mix(mortar, brick, use.x*use.y);
fragcolour*=lightintensity;

colour = vec4(fragcolour, 1.0);
}
