#version 440



uniform vec3 stripecolour;
uniform vec3 backcolour;
uniform float width;
uniform float fuzz;
uniform float scaler;


// Position of the eye (camera)
//uniform vec3 eye_pos;
// Texture to sample from
//uniform sampler2D tex;


// Incoming position
//layout(location = 0) in vec3 position;
// Incoming normal
//layout(location = 1) in vec3 transformed_normal;
// Incoming texture coordinate
//layout(location = 2) in vec2 tex_coord;

layout(location = 0) in vec3 diffusecolour;
layout(location = 1) in vec3 specularcolour;
layout(location = 2) in float texcoord;

// Outgoing colour
layout(location = 0) out vec4 colour;

void main() {
  // *********************************
  // Calculate direction to the light
  /* vec3 light_dir = normalize(light.position - position);
  // Calculate distance to light
  float L = length(light.position - position);
  // Calculate attenuation value
  float Att = light.constant + light.linear*L + light.quadratic*L*L;
  // Calculate spot light intensity
  float Light_intensity = pow(max(dot((-1.0*light.direction),light_dir),0.0),light.power);
  // Calculate light colour
  vec4 LC = (Light_intensity*light.light_colour)/Att;
  // Calculate view direction
   vec3 view_dir = normalize(eye_pos - position);
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
  // Sample texture
   vec4 tex_colour = texture(tex, tex_coord);
  // Calculate primary colour component
  vec4 primary = mat.emissive + diffuse;
  // Calculate final colour - remember alpha
  colour = primary*tex_colour + specular;
  colour.a = 1.0;*/

  float scaledt = fract(texcoord * scaler);
  float frac1 = clamp(scaledt/fuzz, 0.0, 1.0);
  float frac2 = clamp((scaledt-width)/fuzz, 0.0, 1.0);

  frac1 = frac1*(1.0-frac2);
  frac1 = frac1 * frac1 * (3.0-(2.0*frac1));
  vec3 fragcolour = mix(backcolour, stripecolour, frac1);

  fragcolour = fragcolour*diffusecolour + specularcolour;
  colour = vec4(fragcolour, 1.0);
  // *********************************
}