#version 440

// Model transformation matrix
uniform mat4 M;
// Transformation matrix
uniform mat4 MVP;
// Normal matrix
uniform mat3 N;
uniform mat4 MV;

uniform vec3 lightposition;
uniform vec3 lightcolour;
uniform vec3 eye_pos;
uniform vec3 specular;
uniform vec3 ambient;
uniform float kd;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 2) in vec3 normal;
// Incoming texture coordinate
layout(location = 10) in vec2 tex_coord_in;

// Outgoing position
//layout(location = 0) out vec3 vertex_position;
// Outgoing transformed normal
//layout(location = 1) out vec3 transformed_normal;
// Outgoing texture coordinate
//layout(location = 2) out vec2 tex_coord_out;
layout(location = 0) out vec3 diffusecolour;
layout(location = 1) out vec3 specularcolour;
layout(location = 2) out float texcoord;

void main() {
  // Calculate screen position
  gl_Position = MVP * vec4(position, 1.0);
  // *********************************
  // Output other values to fragment shader
  //vertex_position =  (M*vec4(position,1.0)).xyz;
  //transformed_normal = N * normal;
  //tex_coord_out = tex_coord_in;
  
  vec3 ecpos = vec3(MV* vec4(position, 1.0));
  vec3 tnorm = normalize(N*normal);
  vec3 lightvec = normalize(lightposition-ecpos);
  vec3 viewvec = normalize(eye_pos-ecpos);
  vec3 hvec = normalize(viewvec+lightvec);

  float spec = clamp(dot(hvec, tnorm), 0.0, 1.0);
  spec = pow(spec, 16.0);

  diffusecolour = lightcolour * vec3(kd* dot(lightvec, tnorm));
  diffusecolour = clamp(ambient + diffusecolour, 0.0, 1.0);
  specularcolour = clamp((lightcolour*specular*spec), 0.0, 1.0);
  texcoord = tex_coord_in.t;

  // *********************************
}