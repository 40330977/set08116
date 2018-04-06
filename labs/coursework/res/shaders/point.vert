#version 440

// The model matrix
//uniform mat4 M;
// The transformation matrix
uniform mat4 MVP;
//MV matrix
uniform mat4 MV;
// The normal matrix
uniform mat3 N;
uniform vec3 lightpos;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 2) in vec3 normal;
// Incoming texture coordinate
layout(location = 10) in vec2 tex_coord_in;

// Outgoing vertex position
layout(location = 0) out vec3 vertex_position;
// Outgoing transformed normal
//layout(location = 1) out vec3 transformed_normal;
// Outgoing texture coordinate
layout(location = 2) out vec2 tex_coord_out;
layout(location = 1) out float light_intensity;

void main() {
  // Set position
  /*gl_Position = MVP * vec4(position, 1.0);
  // *********************************
  // Output other values to fragment shader
  transformed_normal = N * normal;
  tex_coord_out = tex_coord_in;
  vertex_position =  position;*/
  // *********************************

  vec3 ecpos = vec3(MV*vec4(position, 1.0));
  vec3 tnorm = normalize(vec3(N*normal));
  light_intensity = dot(normalize(lightpos-ecpos), tnorm);
  light_intensity *= 1.5;
  gl_Position = MVP * vec4(position, 1.0);
}