#version 440

// Model transformation matrix
uniform mat4 M;
// Transformation matrix
uniform mat4 MVP;
// Normal matrix
uniform mat3 N;
uniform mat4 MV;

uniform vec3 lightposition;

const float speccon = 0.3;
const float diffcon = 1.0 - speccon;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 2) in vec3 normal;

layout(location = 1) out vec2 modelcoordpos;
layout(location = 2) out float lightintensity;

void(){

vec3 ecposition = vec3(MV*position);
vec3 tnorm = normalize(N*normal);
vec3 lightvec = normalize(lightposition - ecposition);
vec3 reflectvec = reflect(-lightvec, tnorm);
vec3 viewvec = normalize(-ecposition);
float diffuse = max(dot(lightvec, tnorm), 0.0);

float spec = 0.0;

if(diffuse > 0.0)
{
	spec = max(dot(reflectvec, viewvec), 0.0);
	spec = pow(spec, 16.0);
}

lightintensity = diffcon*diffuse+speccon*spec;
modelcoordpos=position.xy;
gl_Position = MVP * vec4(position, 1.0);
}