#version 440

// A directional light structure
struct directional_light {
  vec4 ambient_intensity;
  vec4 light_colour;
  vec3 light_dir;
};

// Material information
struct material {
  vec4 emissive;
  vec4 diffuse_reflection;
  vec4 specular_reflection;
  float shininess;
};

// Point light for the scene
uniform directional_light light;
// Material for the object
uniform material mat;
// Eye position
uniform vec3 eye_pos;
// Texture
uniform sampler2D tex;

uniform vec3 brick;//brick colour
uniform vec3 mortar;//mortar colour
uniform vec2 bsize;//brick size
uniform vec2 bpct;//brick percent
uniform vec2 mpct;//mortar percent

// Incoming position
layout(location = 0) in vec3 position;
// Incoming normal
layout(location = 1) in vec3 transformed_normal;
// Incoming texture coordinate
layout(location = 2) in vec2 tex_coord;

// Outgoing colour
layout(location = 0) out vec4 colour;

vec2 integral(in vec2 x, in vec2 p, in vec2 notp) {    // integral function providing properly weighted average avoiding point sampling aliasing artefacts
vec2 use = ((floor(x)*(p))+ max(fract(x)-(notp), 0.0));
return use;
}

void main() {
  // *********************************
   // Calculate ambient component
  vec4 ambcomp = mat.diffuse_reflection*light.ambient_intensity;
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
  vec4 lightintensity = mat.emissive + ambcomp + diffuse;
  
vec3 fragcolour;
vec2 pos;
vec2 use;
vec2 fw;
vec2 modelcoordpos = position.xy;
pos = modelcoordpos/bsize;

if(fract(pos.y*0.5) > 0.5)//apply offset
{
	pos.x += 0.5;
}

fw = fwidth(pos);//calculate filter

use += (integral(pos+fw, bpct, mpct)-integral(pos, bpct, mpct))/fw;//integral of pulse over the filter width

fragcolour = mix(mortar, brick, use.x*use.y);
fragcolour*=lightintensity.xyz;
fragcolour = fragcolour + specular.xyz;
colour = vec4(fragcolour, 1.0);







  // *********************************
}