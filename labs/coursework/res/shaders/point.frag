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

// Point lights being used in the scene
uniform point_light points[4];
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

// Point light calculation
vec4 calculate_point(in point_light point, in material mat, in vec3 position, in vec3 normal, in vec3 view_dir,
                     in vec4 tex_colour) {
  // *********************************
  // Get distance between point light and vertex
  float L = length(point.position - position);
  // Calculate attenuation factor
  float Att = 1/(point.constant + point.linear*L + point.quadratic*L*L);
  // Calculate light colour
  vec4 LC = Att*point.light_colour;

  // Calculate light dir
  vec3 light_dir = point.position - transformed_normal;
  // Now use standard phong shading but using calculated light colour and direction
  // - note no ambient

  // Calculate diffuse component
  float k = max(dot(transformed_normal, light_dir), 0.0);
  // Calculate diffuse
  vec4 diffuse = k * (mat.diffuse_reflection * LC);
  
  // Calculate half vector
   vec3 halfer = normalize(view_dir+light_dir);
  // Calculate specular component
 float l = pow(max(dot(transformed_normal, halfer), 0.0),mat.shininess);
  vec4 specular = l * LC * mat.specular_reflection;
  
  // Calculate primary colour component
  vec4 primary = mat.emissive + diffuse;
  // Calculate final colour - remember alpha
  colour = primary*tex_colour + specular;
  colour.a = 1.0;





  // *********************************
  return colour;
}


void main() {
   colour = vec4(0.0, 0.0, 0.0, 1.0);
  // *********************************
  // Calculate view direction
  vec3 view_dir = normalize(eye_pos - position);
  // Sample texture
  vec4 tex_colour = texture(tex, tex_coord);
  // Sum point lights
  for (int i = 0; i < 4; ++ i )
 colour += calculate_point ( points [ i ] , mat , position , transformed_normal , 
 view_dir , tex_colour ) ;







  // *********************************
}