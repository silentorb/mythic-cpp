
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
	vec4 translated_position = projection * view * model * vec4(position, 1.0);
	fragment_position = translated_position.xyz;
	fragment_normal = projection * view * model * vec4(normal, 1.0);
    gl_Position = translated_position;
}
