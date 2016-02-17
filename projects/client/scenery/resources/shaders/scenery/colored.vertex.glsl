
#include <scenery/includes/scene>

in vec3 input_position;
in vec4 input_color;
in vec3 input_normal;

out vec4 color;
out vec3 position;
out vec3 normal;

uniform mat4 model;

void main() {
	color = input_color;
	position = input_position;
	normal = input_normal;
    gl_Position = projection * view * model * vec4(input_position, 1.0);
}
