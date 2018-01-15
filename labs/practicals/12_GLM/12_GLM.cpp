#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\projection.hpp>
#include <iostream>

using namespace std;
using namespace glm;

int main() {

	vec2 u(1.0f, 0.0f);
	vec2 z(1.0f, 0.0f);

	vec3 v(1.0f, 0.0f, 0.0f);
	vec3 w(1.0f, 0.0f, 0.0f);

	vec4 x(1.0f, 0.0f, 0.0f, 1.0f);
	vec4 y(1.0f, 0.0f, 0.0f, 1.0f);

	vec3 a(vec2(1.0f, 0.0f), 0.0f);//2d
	vec4 b(vec2(1.0f, 0.0f), 0.0f, 1.0f);

	vec2 c(vec3(1.0f, 0.0f, 0.0f));//3d
	vec4 d(vec3(1.0f, 0.0f, 0.0f), 1.0f);

	vec2 e(vec4(1.0f, 0.0f, 0.0f, 1.0f));//4d
	vec3 f(vec4(1.0f, 0.0f, 0.0f, 1.0f));

	vec2 g = u + z;
	vec2 h = u - z;

	vec3 i = v + w;
	vec3 j = v - w;

	vec4 k = x + y;
	vec4 l = x - y;

	vec2 m = 5.0f*u;
	vec2 n = z / 5.0f;

	vec3 p = 5.0f*v;
	vec3 q = w / 5.0f;

	vec4 r = 5.0f*x;
	vec4 s = y / 5.0f;
}

