#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;
effect eff;
texture tex;
target_camera cam;
vector<point_light> points(4);
//vector<spot_light> spots(5);

bool load_content() {
  // Create meshes
	/*meshes["plane"] = mesh(geometry_builder::create_plane());
	meshes["box1"] = mesh(geometry_builder::create_box());
	meshes["box2"] = mesh(geometry_builder::create_box());
	meshes["disk"] = mesh(geometry_builder::create_disk(20));
	meshes["cylinder"] = mesh(geometry_builder::create_cylinder(20, 20));*/

	meshes["plane"] = mesh(geometry_builder::create_plane());

	// Create scene
	meshes["box"] = mesh(geometry_builder::create_box());
	meshes["box1"] = mesh(geometry_builder::create_box());
	meshes["tetra"] = mesh(geometry_builder::create_tetrahedron());
	meshes["pyramid"] = mesh(geometry_builder::create_pyramid());
	meshes["disk"] = mesh(geometry_builder::create_disk(20));
	meshes["cylinder"] = mesh(geometry_builder::create_cylinder(20, 20));
	meshes["sphere"] = mesh(geometry_builder::create_sphere(20, 20));
	meshes["torus"] = mesh(geometry_builder::create_torus(20, 20, 1.0f, 5.0f));

	// Transform objects
	meshes["box"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["box"].get_transform().translate(vec3(10.0f, 2.5f, -30.0f));
	meshes["box1"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["box1"].get_transform().translate(vec3(-10.0f, 2.5f, -30.0f));
	meshes["tetra"].get_transform().scale = vec3(4.0f, 4.0f, 4.0f);
	meshes["tetra"].get_transform().translate(vec3(-30.0f, 10.0f, -10.0f));
	meshes["pyramid"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["pyramid"].get_transform().translate(vec3(-10.0f, 7.5f, -30.0f));
	meshes["disk"].get_transform().scale = vec3(3.0f, 1.0f, 3.0f);
	meshes["disk"].get_transform().translate(vec3(-10.0f, 11.5f, -30.0f));
	meshes["disk"].get_transform().rotate(vec3(half_pi<float>(), 0.0f, 0.0f));
	meshes["cylinder"].get_transform().scale = vec3(5.0f, 5.0f, 5.0f);
	meshes["cylinder"].get_transform().translate(vec3(-25.0f, 2.5f, -25.0f));
	meshes["sphere"].get_transform().scale = vec3(2.5f, 2.5f, 2.5f);
	meshes["sphere"].get_transform().translate(vec3(-25.0f, 10.0f, -25.0f));
	meshes["torus"].get_transform().translate(vec3(-25.0f, 10.0f, -25.0f));
	meshes["torus"].get_transform().rotate(vec3(half_pi<float>(), 0.0f, 0.0f));

	// Load texture
	tex = texture("C:/Users/40330977/Desktop/set08116/labs/coursework/res/textures/check_1.png");

	// Point 0, Position (-25, 5, -15)
	// Red, 20 range
	points[0].set_position(vec3(-25.0f, 5.0f, -15.0f));
	points[0].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[0].set_range(10.0f);
	// Point 1, Position (-25, 5, -35)
	// blue,20 range
	points[1].set_position(vec3(-25.0f, 5.0f, -35.0f));
	points[1].set_light_colour(vec4(0.0f, 0.0f, 1.0f, 1.0f));
	points[1].set_range(20.0f);
	// Point 2,Position (-10, 5, -15)
	// green,20 range
	points[2].set_position(vec3(-10.0f, 5.0f, -15.0f));
	points[2].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	points[2].set_range(20.0f);
	// Point 3,Position (-10, 5, -35)
	// white,20 range
	points[3].set_position(vec3(-10.0f, 5.0f, -35.0f));
	points[3].set_light_colour(vec4(1.0f, 1.0f, 1.0f, 1.0f));
	points[3].set_range(20.0f);
	

	// Load in shaders
	eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/point.vert", GL_VERTEX_SHADER);
	eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/point.frag", GL_FRAGMENT_SHADER);

  // Build effect
  eff.build();

  // Set camera properties
  cam.set_position(vec3(0.0f, 0.0f, 10.0f));
  cam.set_target(vec3(0.0f, 0.0f, 0.0f));
  cam.set_projection(quarter_pi<float>(), renderer::get_screen_aspect(), 0.1f, 1000.0f);
  return true;
}


bool update(float delta_time) {

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

	//if (glfwGetKey(renderer::get_window(), GLFW_KEY_UP)) {
		meshes["box"].get_transform().rotate(vec3(0.0f,  -pi<float>() * delta_time,  0.0f ));
	//}
	// rotate Box Two on Z axis by delta_time
	//if (glfwGetKey(renderer::get_window(), GLFW_KEY_UP)) {
		meshes["box1"].get_transform().rotate(vec3(0.0f, -pi<float>() * delta_time, 0.0f));
	//}
	// Rotate the sphere
	meshes["sphere"].get_transform().rotate(vec3(0.0f, half_pi<float>(), 0.0f) * delta_time);

  // Update the camera
  cam.update(delta_time);
  return true;
}

bool render() {
	// Render meshes
	for (auto &e : meshes) {
		auto m = e.second;
		// Bind effect
		renderer::bind(eff);
		// Create MVP matrix
		auto M = m.get_transform().get_transform_matrix();
		auto V = cam.get_view();
		auto P = cam.get_projection();
		auto MVP = P * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("MVP"), // Location of uniform
			1,                               // Number of values - 1 mat4
			GL_FALSE,                        // Transpose the matrix?
			value_ptr(MVP));                 // Pointer to matrix data
											 // *********************************
											 // Set M matrix uniform
		glUniformMatrix4fv(eff.get_uniform_location("M"), 1, GL_FALSE, value_ptr(M));
		// Set N matrix uniform - remember - 3x3 matrix
		glUniformMatrix3fv(eff.get_uniform_location("N"), 1, GL_FALSE, value_ptr(m.get_transform().get_normal_matrix()));
		// Bind material
		renderer::bind(m.get_material(), "mat");
		// Bind point lights
		renderer::bind(points, "points");
		// Bind spot lights
		//renderer::bind(spots, "spots");
		// Bind texture
		renderer::bind(tex, 0);
		// Set tex uniform
		glUniform1i(eff.get_uniform_location("tex"), 0);
		// Set eye position- Get this from active camera
		vec3 eye_pos = cam.get_position();
		glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(eye_pos));
		// Render mesh
		renderer::render(m);
		// *********************************
	}

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