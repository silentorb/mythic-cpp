
#include <scenery/includes/scene>

in vec3 position;
in vec3 normal;
in vec4 color;

out vec4 fragment_color;
out vec3 fragment_position;
out vec3 fragment_normal;

uniform mat4 model;

void main() {
	fragment_color = color;
	fragment_position = position;
	fragment_normal = normal;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
