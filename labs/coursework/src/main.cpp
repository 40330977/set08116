#include <glm\glm.hpp>
#include <graphics_framework.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

std::array<mesh, 4> meshes;
//std::array<texture, 3> textures;
mesh plane_mesh;
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
//shadow_map shadow;
//int width, height;

/*void perlingen() {
	float* p = new float[256];
	default_random_engine e;
	uniform_int_distribution<> dist(0, 255);
	auto n = dist(e);
	int i;

	for (i = 0; i < 255; i++) {

		p[i] = n;

	}

	//int[256] permutation = { 151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };



}*/





bool load_content() {
	//shadow attempt code
	// Create shadow map- use screen size
	//glfwGetFramebufferSize(renderer::get_window(), &width, &height);
	//shadow = shadow_map(width, height);

	plane_mesh = mesh(geometry_builder::create_plane());

	// Create scene
	meshes[0] = mesh(geometry_builder::create_sphere(20, 20));
	meshes[1] = mesh(geometry_builder::create_sphere(20, 20));
	meshes[2] = mesh(geometry_builder::create_sphere(20, 20));
	meshes[3] = mesh(geometry_builder::create_cylinder(20, 20));
	
	
	
	meshes[0].get_transform().position += vec3(0.0f, 10.0f, 0.0f);
	
	meshes[1].get_transform().position += vec3(0.0f, -8.0f, 0.0f);
	
	meshes[2].get_transform().position += vec3(0.0f, 1.0f, 10.0f);

	meshes[3].get_transform().position += vec3(4.0f, 0.0f, 0.0f);


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

	

	// Load texture
	//tex = texture("C:/Users/40330977/Desktop/set08116/labs/coursework/res/textures/check_1.png");

	//plane_tex = texture("C:/Users/40330977/Desktop/set08116/labs/coursework/res/textures/check_1.png");

	//noise = texture("C:/Users/40330977/Desktop/CW/bin/bin/Debug/res/textures/perlin2d.png");
	//noise = texture("C:/Users/40330977/Desktop/CW/bin/bin/Debug/res/textures/Perlin_Noise.raw");
	
	/*// Spot 0, Position (-25, 10, -15)  
	// Green, Direction (1, -1, -1) normalized
	// 20 range,0.5 power
	spots[0].set_position(vec3(-25.0f, 10.0f, -15.0f));
	spots[0].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	spots[0].set_direction(normalize(vec3(1.0f, -1.0f, -1.0f)));
	spots[0].set_range(20.0f);
	spots[0].set_power(0.5f);
	// Spot 1,Position (-25, 10, -35)
	// Blue,Direction (1, -1, 1) normalized
	// 20 range,0.5 power
	spots[1].set_position(vec3(-25.0f, 10.0f, -35.0f));
	spots[1].set_light_colour(vec4(0.0f, 0.0f, 1.0f, 1.0f));
	spots[1].set_direction(normalize(vec3(1.0f, -1.0f, -1.0f)));
	spots[1].set_range(20.0f);
	spots[1].set_power(0.5f);
	// Spot 2,Position (-10, 10, -15)
	// Green,Direction (-1, -1, -1) normalized
	// 20 range,0.5 power
	spots[2].set_position(vec3(-10.0f, 10.0f, -15.0f));
	spots[2].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	spots[2].set_direction(normalize(vec3(-1.0f, -1.0f, -1.0f)));
	spots[2].set_range(20.0f);
	spots[2].set_power(0.5f);
	// Spot 3,Position (-10, 10, -35)
	// Green,Direction (-1, -1, 1) normalized
	// 20 range,0.5 power
	spots[3].set_position(vec3(-10.0f, 10.0f, -15.0f));
	spots[3].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	spots[3].set_direction(normalize(vec3(-1.0f, -1.0f, 1.0f)));
	spots[3].set_range(20.0f);
	spots[3].set_power(0.5f);
	// Spot 4,Position (-17.5, 15, -25)
	// Blue,Direction (0, -1, 0)
	// 30 range,1.0 power
	spots[4].set_position(vec3(-17.5f, 15.0f, -25.0f));
	spots[4].set_light_colour(vec4(0.0f, 0.0f, 1.0f, 1.0f));
	spots[4].set_direction(normalize(vec3(0.0f, -1.0f, 0.0f)));
	spots[4].set_range(30.0f);
	spots[4].set_power(1.0f);
	// Point 0, Position (-25, 5, -15)
	// Red, 20 range
	points[0].set_position(vec3(-25.0f, 5.0f, -15.0f));
	points[0].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[0].set_range(10.0f);
	// Point 1, Position (-25, 5, -35)
	// red,20 range
	points[1].set_position(vec3(-25.0f, 5.0f, -35.0f));
	points[1].set_light_colour(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	points[1].set_range(20.0f);
	// Point 2,Position (-10, 5, -15)
	// green,20 range
	points[2].set_position(vec3(-10.0f, 5.0f, -15.0f));
	points[2].set_light_colour(vec4(0.0f, 1.0f, 0.0f, 1.0f));
	points[2].set_range(20.0f);
	// Point 3,Position (-10, 5, -35)
	// blue,20 range
	points[3].set_position(vec3(-10.0f, 5.0f, -35.0f));
	points[3].set_light_colour(vec4(0.0f, 0.0f, 1.0f, 1.0f));
	points[3].set_range(20.0f);*/
	
	
	
	// Load in shaders
	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/multi-light.vert", GL_VERTEX_SHADER);
	//eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/multi-light.frag", GL_FRAGMENT_SHADER);

	eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/spot.vert", GL_VERTEX_SHADER);
	eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/spot.frag", GL_FRAGMENT_SHADER);

	//vector<string> fragshaders{ "C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/multi-light.frag", /*"C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/part_shadow.frag",
	//"C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/part_spot.frag",  "C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/part_point.frag"*/ };
	//shadow_eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/spot.vert", GL_VERTEX_SHADER);
	//shadow_eff.add_shader("C:/Users/40330977/Desktop/set08116/labs/coursework/res/shaders/spot.frag", GL_FRAGMENT_SHADER);

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

		//rotation of meshes
		meshes[0].get_transform().rotate(vec3(0.0f,  -pi<float>() * delta_time,  0.0f ));
	
		meshes[1].get_transform().rotate(vec3(0.0f, -pi<float>() * delta_time, 0.0f));

		meshes[2].get_transform().rotate(vec3(0.0f, -pi<float>() * delta_time, 0.0f));

	
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

	//shadow attempt code
	// Update the shadow map light_position from the spot light
	//shadow.light_position = spots[1].get_position();
	// do the same for light_dir property
	//shadow.light_dir = spots[1].get_direction();
  
  return true;
}

bool render() {
	//shadow attempt code
	/*// Set render target to shadow map
	renderer::set_render_target(shadow);
	// Clear depth buffer bit
	glClear(GL_DEPTH_BUFFER_BIT);
	// Set face cull mode to front
	glCullFace(GL_FRONT);
	// *********************************

	// We could just use the Camera's projection, 
	// but that has a narrower FoV than the cone of the spot light, so we would get clipping.
	// so we have yo create a new Proj Mat with a field of view of 90.
	mat4 LightProjectionMat = perspective<float>(90.f, renderer::get_screen_aspect(), 0.1f, 1000.f);

	// Bind shader
	renderer::bind(shadow_eff);
	// Render meshes
	for (size_t k = 0; k < meshes.size(); k++) {
		// *********************************
		// SET M to be the usual mesh  transform matrix
		auto M = meshes[k].get_transform().get_transform_matrix();
		// Create MVP matrix
		
		// *********************************
		// View matrix taken from shadow map
		auto V = shadow.get_view();
		// *********************************
		auto MVP = LightProjectionMat * V * M;
		// Set MVP matrix uniform
		glUniformMatrix4fv(shadow_eff.get_uniform_location("MVP"), // Location of uniform
			1,                                      // Number of values - 1 mat4
			GL_FALSE,                               // Transpose the matrix?
			value_ptr(MVP));                        // Pointer to matrix data
													// Render mesh
		renderer::render(meshes[k]);
	}
	// *********************************
	renderer::set_render_target();
	// Set face cull mode to back
	glCullFace(GL_BACK);*/
	// *********************************

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
	vec3 backcolour = vec3(0.0, 1.0, 0.0);
	float width = 0.5;
	float fuzz = 0.5;
	float scaler = 0.5;
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
		//renderer::bind(spots, "spots");
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
		//glUniform3fv(eff.get_uniform_location("sky"), 1, value_ptr(sky));
		//glUniform3fv(eff.get_uniform_location("cloud"), 1, value_ptr(cloud));
		//set texture
		//glUniform1i(eff.get_uniform_location("tex"), 0);
		//glUniform1i(eff.get_uniform_location("noise"), 0);

		// Set eye position- Get this from active camera
		vec3 eye_pos = cam.get_position();
		glUniform3fv(eff.get_uniform_location("eye_pos"), 1, value_ptr(eye_pos));

		//shadow attempt code
		/*auto lM = M;
		// viewmatrix from the shadow map
		auto lV = shadow.get_view();
		// Multiply together with LightProjectionMat
		auto lP = cam.get_projection();
		auto lightMVP = lP*lV*lM;
		// Set uniform
		glUniformMatrix4fv(eff.get_uniform_location("lightMVP"), // Location of uniform
			1,                                    // Number of values - 1 mat4
			GL_FALSE,                             // Transpose the matrix?
			value_ptr(lightMVP));
		// Bind material*/
		
		
		// Bind texture
		
		// Bind shadow map texture - use texture unit 1
		//renderer::bind(shadow.buffer->get_depth(), 1);
		// Set the shadow_map uniform
		//glUniform1i(eff.get_uniform_location("shadow_map"), 1);


		// Bind texture to renderer
		//renderer::bind(tex, 0);
		//renderer::bind(noise, 0);

		
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