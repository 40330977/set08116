#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

geometry geom;
effect eff;
target_camera cam;

// Helper method - adds a triangle to geometry
void triangle(const vector<vec3> &points, vector<vec3> &positions, vector<vec4> &colours) {
  positions.insert(positions.end(), points.begin(), points.end());
  for (auto i = 0; i < 3; ++i){
    colours.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
  }

}

void divide_triangle(const vector<vec3> &points, unsigned int count, vector<vec3> &positions, vector<vec4> &colours) {
  // *********************************
  // IF we have more divisions to do?
	
	/*vec3 v0 = vec3(1.0f, -1.0f, 0.0f);
	vec3 v1 = vec3(0.0f, 1.0f, 0.0f);
	vec3 v2 = vec3(-1.0f, -1.0f, 0.0f);

	vec3 m0 = (v0 + v1) / 2.0f;
	vec3 m1 = (v1 + v2) / 2.0f;
	vec3 m2 = (v2 + v0) / 2.0f;

	triangle({ v0,m0,m2 }, positions, colours);
	triangle({ m1,v2,m2 }, positions, colours);
	triangle({ m0,v1,m1 }, positions, colours);*/
	
	//triangle({ vec3(1.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(-1.0f, -1.0f, 0.0f) }, positions, colours);
	

	if (count > 0)
	{
		count--;
		vec3 m0 = (points[0] + points[1]) / 2.0f;
		vec3 m1 = (points[1] + points[2]) / 2.0f;
		vec3 m2 = (points[2] + points[0]) / 2.0f;
		divide_triangle({ points[0],m0,m2 }, count, positions, colours);
		divide_triangle({ m1,points[2],m2 }, count, positions, colours);
		divide_triangle({ m0,points[1],m1 }, count, positions, colours);
	}
	else
	{
		triangle(points, positions, colours);
	}

	


    // Calculate new vertices to work on

    // Divide new triangles





	
  // *********************************
}

bool load_content() {
  // Required buffers
  vector<vec3> positions;
  vector<vec4> colours;
  divide_triangle({vec3(1.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(-1.0f, -1.0f, 0.0f)}, 4, positions, colours);

  // Add to the geometry
  geom.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
  geom.add_buffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);

  // Load in shaders
  eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
  eff.add_shader("shaders/basic.frag", GL_FRAGMENT_SHADER);
  // Build effect
  eff.build();

  // Set camera properties
  cam.set_position(vec3(3.0f, 3.0f, 3.0f));
  cam.set_target(vec3(0.0f, 0.0f, 0.0f));
  auto aspect = static_cast<float>(renderer::get_screen_width()) / static_cast<float>(renderer::get_screen_height());
  cam.set_projection(quarter_pi<float>(), aspect, 2.414f, 1000.0f);
  return true;
}

bool update(float delta_time) {
  // Update the camera
  cam.update(delta_time);
  return true;
}

bool render() {
  // Bind effect
  renderer::bind(eff);
  // Create MVP matrix
  mat4 M(1.0f);
  auto V = cam.get_view();
  auto P = cam.get_projection();
  auto MVP = P * V * M;
  // Set MVP matrix uniform
  glUniformMatrix4fv(eff.get_uniform_location("MVP"), 1, GL_FALSE, value_ptr(MVP));
  // Render geometry
  renderer::render(geom);
  return true;
}

void main() {
  // Create application
  app application("22_Sierpinski_Gasket");
  // Set load content, update and render methods
  application.set_load_content(load_content);
  application.set_update(update);
  application.set_render(render);
  // Run application
  application.run();
}