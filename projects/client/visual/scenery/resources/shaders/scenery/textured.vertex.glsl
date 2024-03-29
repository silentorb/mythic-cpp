
#include <scene>

//in vec3 input_position;
//in vec3 input_normal;
in vec2 uv;

out vec2 texture_coordinates;
//out vec3 normal;
//out vec3 position;

uniform mat4 model;

void main() {
	texture_coordinates = uv;
//	normal = input_normal;
//	position = input_position;
    gl_Position = scene.projection * scene.view * model * vec4(input_position, 1.0);
}
