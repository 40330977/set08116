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
//uniform sampler2D tex;
uniform vec3 stripecolour;
uniform vec3 backcolour;
uniform float width;
uniform float fuzz;
uniform float scaler;

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
   //vec4 tex_colour = texture(tex, tex_coord);
   
   float scaledt = fract(tex_coord.t * scaler);//calculate where in the stripe pattern the coordinate is
  float frac1 = clamp(scaledt/fuzz, 0.0, 1.0);
  float frac2 = clamp((scaledt-width)/fuzz, 0.0, 1.0);//where the pixel is in relation to the transition between colours

  frac1 = frac1*(1.0-frac2);//used to blend the two colours
  frac1 = frac1 * frac1 * (3.0-(2.0*frac1));//hermite interpolation to blend colours
  vec3 fragcolour = mix(backcolour, stripecolour, frac1);//mix the colours
  vec4 fragcolours = vec4(fragcolour, 1.0);
  // Calculate primary colour component
  vec4 primary = mat.emissive + diffuse;
  // Calculate final colour - remember alpha
  colour = primary*fragcolours + specular;
  //colour *= fragcolours;
  colour.a = 1.0;
  
  /*float scaledt = fract(tex_coord.x * scaler);//calculate where in the stripe pattern the coordinate is
  float frac1 = clamp(scaledt/fuzz, 0.0, 1.0);
  float frac2 = clamp((scaledt-width)/fuzz, 0.0, 1.0);//where the pixel is in relation to the transition between colours

  frac1 = frac1*(1.0-frac2);//used to blend the two colours
  frac1 = frac1 * frac1 * (3.0-(2.0*frac1));//hermite interpolation to blend colours
  vec3 fragcolour = mix(backcolour, stripecolour, frac1);//mix the colours
  vec4 fragcolours = vec4(fragcolour, 1.0);
  fragcolours = fragcolours*diffuse + specular;//apply specular
  colour = fragcolours;*/

  // *********************************
}