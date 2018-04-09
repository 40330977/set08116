#version 440

// Material information
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};


// Point lights being used in the scene
//uniform point_light points[4];
 Material for the object
//uniform material mat;
// Eye position
//uniform vec3 eye_pos;
// Texture
//uniform sampler2D tex;
uniform sampler3D noise;
uniform vec3 sky;
uniform vec3 cloud;

// Incoming position
layout(location = 0) in vec3 vertex_position;
// Incoming normal
//layout(location = 1) in vec3 transformed_normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;
layout(location = 1) in float light_intensity;

// Outgoing colour
layout(location = 0) out vec4 colour;




void main() {
   //colour = vec4(0.0, 0.0, 0.0, 1.0);
  // *********************************
  // Calculate view direction
  //vec3 view_dir = normalize(eye_pos - vertex_position);
  // Sample texture
  //vec4 tex_colour = texture(tex, tex_coord);
  // Sum point lights
  //for (int i = 0; i < 4; ++ i )
 //colour += calculate_point ( points [ i ] , mat , vertex_position , transformed_normal , 
 //view_dir , tex_colour ) ;

 //vec3 sky = vec3(0.0,0.0,0.8);
 //vec3 cloud = vec3(0.8,0.8,0.8);

 //vec3 noiser = vec3(noise, 1.0);
 vec4 noisevec = texture(noise, vertex_position);

 float intensity =  (noisevec[0]+noisevec[1]+noisevec[2]+noisevec[3]+0.03125)*1.5;

 vec3 col = mix(sky,cloud,intensity) * light_intensity;

 colour = vec4(col, 1.0);
  // *********************************
}