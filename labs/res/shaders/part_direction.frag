// Directional light structure
#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT
struct directional_light
{
	vec4 ambient_intensity;
	vec4 light_colour;
	vec3 light_dir;
};
#endif

// A material structure
#ifndef MATERIAL
#define MATERIAL
struct material
{
	vec4 emissive;
	vec4 diffuse_reflection;
	vec4 specular_reflection;
	float shininess;
};
#endif

// Calculates the directional light
vec4 calculate_direction(in directional_light light, in material mat, in vec3 normal, in vec3 view_dir, in vec4 tex_colour)
{
 // *********************************
	// Calculate ambient component
	vec4 ambcomp = mat.diffuse_reflection*light.ambient_intensity;
	// Calculate diffuse component :  (diffuse reflection * light_colour) *  max(dot(normal, light direction), 0)
	
	float k = max(dot(normal, light.light_dir),0.0);
	vec4 diffuse = (mat.diffuse_reflection * light.light_colour)* k;
	// Calculate normalized half vector 
	vec3 halfer = normalize(view_dir+light.light_dir);
	// Calculate specular component : (specular reflection * light_colour) * (max(dot(normal, half vector), 0))^mat.shininess
	vec4 specular = pow(max(dot(normal, halfer), 0.0),mat.shininess) * (light.light_colour * mat.specular_reflection);
 // *********************************
	// Calculate colour to return
	vec4 colour = ((mat.emissive + ambcomp + diffuse) * tex_colour) + specular;
	colour.a = 1.0;
	// Return colour
	return colour;

}
