#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

std::array<mesh, 4> meshes;
//std::array<texture, 3> textures;
mesh plane_mesh;
mesh teapot;
texture plane_tex;
//map<string, mesh> meshes;
effect eff;
//effect shadow_eff;
texture tex;
texture noise;
target_camera cam;
vector<point_light> points(4);
vector<spot_light> spots(5);
double cursor_x = 0.0;
double cursor_y = 0.0;
double xpos;
double ypos;
free_camera cam1;
point_light light;






bool load_content() {
	//shadow attempt code
	// Create shadow map- use screen size
	//glfwGetFramebufferSize(renderer::get_window(), &width, &height);
	//shadow = shadow_map(width, height);

	//teapot = mesh(geometry("C:/Users/40330977/Desktop/set08116/labs/res/models/teapot.obj"));

	plane_mesh = mesh(geometry_builder::create_plane());

	// Create scene
	meshes[0] = mesh(geometry_builder::create_sphere(20, 20));
	//meshes[0] = mesh(geometry_builder::create_box(vec3(20,20,20)));
	meshes[1] = mesh(geometry_builder::create_sphere(20, 20));
	meshes[2] = mesh(geometry_builder::create_sphere(20, 20));
	meshes[3] = mesh(geometry_builder::create_cylinder(20, 20));
	
	
	
	meshes[0].get_transform().position += vec3(0.0f, 10.0f, 0.0f);
	//meshes[1].get_transform().position += vec3(0.0f, -8.0f, 0.0f);
	meshes[2].get_transform().position += vec3(5.0f, 1.0f, 3.0f);
	meshes[3].get_transform().position += vec3(4.0f, 0.0f, 0.0f);

	meshes[0].get_transform().scale += 5.0f;

	//teapot.get_transform().scale = (vec3(0.01f, 0.01f, 0.01f));
	
	

	// - all emissive is black
	// - all specular is white
	// - all shininess is 25
	
	meshes[0].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes[0].get_material().set_diffuse(vec4(1.0f, 0.0f, 1.0f, 1.0f));
	meshes[0].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes[0].get_material().set_shininess(25.0f);

	meshes[1].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes[1].get_material().set_diffuse(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	meshes[1].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes[1].get_material().set_shininess(25.0f);

	meshes[2].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes[2].get_material().set_diffuse(vec4(1.0f, 1.0f, 0.0f, 1.0f));
	meshes[2].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes[2].get_material().set_shininess(25.0f);

	meshes[3].get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	meshes[3].get_material().set_diffuse(vec4(1.0f, 1.0f, 0.0f, 1.0f));
	meshes[3].get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	meshes[3].get_material().set_shininess(25.0f);

	plane_mesh.get_material().set_emissive(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	plane_mesh.get_material().set_diffuse(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	plane_mesh.get_material().set_specular(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	plane_mesh.get_material().set_shininess(25.0f);

	// Set lighting values, Position (-25, 10, -10)
	light.set_position(vec3(-25.0f, 10.0f, -10.0f));
	// Light colour white
	light.set_light_colour(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	// Set range to 20
	light.set_range(20.0f);

	light.set_constant_attenuation(1.0f);
	light.set_linear_attenuation(1.0f);
	light.set_quadratic_attenuation(1.0f);
	
	
	
	// Load texture
	//tex = texture("C:/Users/40330977/Desktop/set08116/labs/coursework/res/textures/check_1.png");

	//plane_tex = texture("C:/Users/40330977/Desktop/set08116/labs/coursework/res/textures/check_1.png");
	
	// Load in shaders
	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/multi-light.vert", GL_VERTEX_SHADER);
	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/multi-light.frag", GL_FRAGMENT_SHADER);

	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/spot.vert", GL_VERTEX_SHADER);
	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/spot.frag", GL_FRAGMENT_SHADER);

	eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/brick.vert", GL_VERTEX_SHADER);
	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/brick.frag", GL_FRAGMENT_SHADER);
	eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/brickantialiased.frag", GL_FRAGMENT_SHADER);

	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/lattice.vert", GL_VERTEX_SHADER);
	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/lattice.frag", GL_FRAGMENT_SHADER);

  // Build effect
  eff.build();
  //shadow_eff.build();

  // Set camera properties
  cam.set_position(vec3(0.0f, 0.0f, 10.0f));
  cam.set_target(vec3(0.0f, 0.0f, 0.0f));
  cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
 

  cam1.set_position(vec3(0.0f, 10.0f, 0.0f));
  cam1.set_target(vec3(0.0f, 0.0f, 0.0f));
  cam1.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
  return true;
}


bool update(float delta_time) {

	//free camera 
	static double ratio_width = quarter_pi<float>() / static_cast<float>(renderer::get_screen_width());
	static double ratio_height =
		(quarter_pi<float>() *
		(static_cast<float>(renderer::get_screen_height()) / static_cast<float>(renderer::get_screen_width()))) /
		static_cast<float>(renderer::get_screen_height());
	//free cam variables
	double current_x;
	double current_y;
	double deltax;
	double deltay;
	double deltaxr;
	double deltayr;
	vec3 direction = vec3(0.0f, 0.0f, 0.0f);
	float movespeed = 50.0f;

	glfwGetCursorPos(renderer::get_window(), &xpos, &ypos);
	// Calculate delta of cursor positions from last frame
	current_x = xpos;
	current_y = ypos;
	deltax = current_x - cursor_x;
	deltay = current_y - cursor_y;
	// Multiply deltas by ratios - gets actual change in orientation
	deltaxr = deltax*ratio_width;
	deltayr = deltay*ratio_height;
	// Rotate cameras by delta
	

	cam1.rotate(deltaxr, -deltayr);

	//target cam positions
	if (glfwGetKey(renderer::get_window(), '1')) {
		cam.set_position(vec3(50, 10, 50));
	}
	if (glfwGetKey(renderer::get_window(), '2')) {
		cam.set_position(vec3(-50, 10, 50));
	}
	if (glfwGetKey(renderer::get_window(), '3')) {
		cam.set_position(vec3(-50, 10, -50));
	}
	if (glfwGetKey(renderer::get_window(), '4')) {
		cam.set_position(vec3(50, 10, -50));
	}

	
	//movement controls for free cam
	if (glfwGetKey(renderer::get_window(), 'W')) {
		direction = +vec3(0.0f, 0.0f, 1.0f);
	}


	if (glfwGetKey(renderer::get_window(), 'A')) {
		direction = +vec3(-1.0f, 0.0f, 0.0f);
	}


	if (glfwGetKey(renderer::get_window(), 'S')) {
		direction = +vec3(0.0f, 0.0f, -1.0f);;
	}


	if (glfwGetKey(renderer::get_window(), 'D')) {
		direction = +vec3(1.0f, 0.0f, 0.0f);
	}

	direction = direction*movespeed*delta_time;

		

	
  // Update the camera
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_SPACE)) {
		cam1.move(direction);
		// Update the camera
		cam1.update(delta_time);

	}
	else { cam.update(delta_time); }

	// Update cursor pos
	cursor_x = current_x;//used without innitialised
	cursor_y = current_y;
  
  return true;
}

bool render() {
	

	renderer::bind(eff);
	// Get PV
	const auto PV = cam.get_projection() * cam.get_view();
	const auto PV1 = cam1.get_projection() * cam1.get_view();
	const auto V = cam.get_view();
	const auto V1 = cam1.get_view();
	vec3 lightpos = vec3(-25, 10, -15);
	vec3 lightcolour = vec3(1.0, 1.0, 1.0);
	vec3 specular = vec3(0.5, 0.5, 0.5);
	vec3 ambient = vec3(0.5, 0.5, 0.5);
	float kd = 0.5;
	vec3 stripecolour = vec3(1.0, 0.0, 0.0);
	vec3 backcolour = vec3(0.0, 0.0, 1.0);
	vec3 brick = vec3(1.0, 0.3, 0.3);
	vec3 mortar = vec3(0.5, 0.5, 0.5);
	//vec3 brick = vec3(0.3, 0.3, 0.3);//ds
	//vec3 mortar = vec3(0.8, 0.8, 0.8);//ds
	vec2 bsize = vec2(0.2, 0.2);
	//vec2 bpct = vec2(0.8, 0.5);//ds
	vec2 bpct = vec2(0.8, 0.8);
	vec2 mpct = vec2(0.2, 0.2);
	float width = 0.5;
	float fuzz = 0.5;
	float scaler = 5.0;
	vec2 scalel = vec2(1.0, 1.0);
	vec2 threshold = vec2(0.3, 0.3);
	vec3 surface = vec3(0.5, 0.5, 0.5);

	//vec3 sky = vec3(0.0, 0.0, 0.8);
	//vec3 cloud = vec3(0.8, 0.8, 0.8);
	// Set the texture value for the shader here
	glUniform1i(eff.get_uniform_location("tex"), 0);
	// Find the lcoation for the MVP uniform
	const auto loc = eff.get_uniform_location("MVP");
	const auto mver = eff.get_uniform_location("MV");


	// Render meshes
	for (size_t i = 0; i < meshes.size(); i++) {
		// *********************************
		// SET M to be the usual mesh  transform matrix
		auto M = meshes[i].get_transform().get_transform_matrix();
		auto N = meshes[i].get_transform().get_normal_matrix();
		// *********************************
		int f = i;
		// Apply the heirarchy chain
		for (size_t j = i; j > 0; j--) {
			M = meshes[j - 1].get_transform().get_transform_matrix() * M;
			N = meshes[j - 1].get_transform().get_normal_matrix()*N;
		}
		// Find the lcoation for the MVP uniform
		
		

		// Set MVP matrix uniform
		if (glfwGetKey(renderer::get_window(), GLFW_KEY_SPACE)) {
			glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(PV1 * M));
			glUniformMatrix4fv(mver, 1, GL_FALSE, value_ptr(V1 * M));
		}
		else {
			glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(PV * M));
			glUniformMatrix4fv(mver, 1, GL_FALSE, value_ptr(V * M));
		}





		//set M
		glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
		// Set N  
		glUniformMatrix3fv(eff.get_uniform_location("N"), 1, GL_FALSE, value_ptr(N));
		renderer::bind(meshes[f].get_material(), "mat");
		// Bind point lights
		//renderer::bind(points, "points");
		// Bind spot lights
		renderer::bind(light, "light");
		glUniform3fv(eff.get_uniform_location("lightpos"), 1, value_ptr(lightpos));
		glUniform3fv(eff.get_uniform_location("lightcolour"), 1, value_ptr(lightcolour));
		glUniform3fv(eff.get_uniform_location("specular"), 1, value_ptr(specular));
		glUniform3fv(eff.get_uniform_location("ambient"), 1, value_ptr(ambient));
		glUniform3fv(eff.get_uniform_location("stripecolour"), 1, value_ptr(stripecolour));
		glUniform3fv(eff.get_uniform_location("backcolour"), 1, value_ptr(backcolour));
		glUniform1f(eff.get_uniform_location("kd"), kd);
		glUniform1f(eff.get_uniform_location("width"), width);
		glUniform1f(eff.get_uniform_location("fuzz"), fuzz);
		glUniform1f(eff.get_uniform_location("scaler"), scaler);
		glUniform3fv(eff.get_uniform_location("brick"), 1, value_ptr(brick));
		glUniform3fv(eff.get_uniform_location("mortar"), 1, value_ptr(mortar));
		glUniform2fv(eff.get_uniform_location("bsize"), 1, value_ptr(bsize));
		glUniform2fv(eff.get_uniform_location("bpct"), 1, value_ptr(bpct));
		glUniform2fv(eff.get_uniform_location("mpct"), 1, value_ptr(mpct));
		glUniform2fv(eff.get_uniform_location("scalel"), 1, value_ptr(scalel));
		glUniform2fv(eff.get_uniform_location("threshold"), 1, value_ptr(threshold));
		glUniform3fv(eff.get_uniform_location("surface"), 1, value_ptr(surface));

		// Set eye position- Get this from active camera
		vec3 eye_pos = cam.get_position();
		glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(eye_pos));
		
		// Render mesh
		renderer::render(meshes[f]);
	}
	


	// Render floor
	if (glfwGetKey(renderer::get_window(), GLFW_KEY_SPACE)) {
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(PV1 * plane_mesh.get_transform().get_transform_matrix()));
	}
	else {
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(PV * plane_mesh.get_transform().get_transform_matrix()));
	}
	
	//bind material
	//renderer::bind(plane_mesh.get_material(), "mat");
	// Bind floor texture
	//renderer::bind(plane_tex, 0);
	// Render floor
	renderer::render(plane_mesh);
	//renderer::render(teapot);
	
	return true;

	
}

void main() {
  // Create application
  app application("Graphics Coursework");
  // Set load content, update and render methods
  application.set_load_content(load_content);
  application.set_update(update);
  application.set_render(render);
  // Run application
  application.run();
}