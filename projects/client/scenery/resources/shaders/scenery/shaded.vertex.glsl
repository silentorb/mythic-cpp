
#include <scenery/includes/scene>

in vec3 input_position;
in vec3 input_normal;

out vec3 normal;
out vec3 position;

uniform mat4 model;

void main() {
	normal = input_normal;
	position = input_position;
    gl_Position = scene.projection * scene.view * model * vec4(input_position, 1.0);
}
