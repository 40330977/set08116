#version 440

// Point light information
struct point_light {
  vec4 light_colour;
  vec3 position;
  float constant;
  float linear;
  float quadratic;
};

// Material information
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Point light for the scene
uniform point_light point;
// Material for the object
uniform material mat;
// Eye position
uniform vec3 eye_pos;
// Texture
uniform sampler2D tex;

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 transformed_normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() {
  // *********************************
  // Get distance between point light and vertex
  vec3 L = light.position - position;
  // Calculate attenuation factor
  vec3 Att = 1/(constant + linear*L + quadratic*L*L);
  // Calculate light colour
  vec3 LC = Att*light.light_colour;

  // Calculate light dir
  vec3 light_dir = light.position - transformed_normal;
  // Now use standard phong shading but using calculated light colour and direction
  // - note no ambient
   // Calculate diffuse component
  float k = max(dot(transformed_normal, light.light_dir), 0.0);
  // Calculate diffuse
  vec4 diffuse = k * (mat.diffuse_reflection * light.light_colour);
  // Calculate view direction
  vec3 view_dir = normalize(eye_pos - position);
  // Calculate half vector
   vec3 halfer = normalize(view_dir+light.light_dir);
  // Calculate specular component
  float l = pow(max(dot(transformed_normal, halfer), 0.0),mat.shininess);
  vec4 specular = l * light.light_colour * mat.specular_reflection;
  // Sample texture
   vec4 tex_colour = texture(tex, tex_coord);
  // Calculate primary colour component
  vec4 primary = mat.emissive + diffuse;
  // Calculate final colour - remember alpha
  colour = primary*tex_colour + specular;
  colour.a = 1.0;







  // *********************************
}