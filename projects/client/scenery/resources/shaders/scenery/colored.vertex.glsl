
#include <scene>

in vec3 input_position;
in vec4 input_color;

out vec4 color;
out vec3 position;

uniform mat4 model;

void main() {
	color = input_color;
	position = input_position;
    gl_Position = scene.projection * scene.view * model * vec4(input_position, 1.0);
}
