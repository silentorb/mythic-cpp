
#include <scenery/includes/scene>
#include <space/includes/lighting>

in vec3 position;
in vec3 normal;
in vec4 color;

out vec4 fragment_color;
out vec3 fragment_position;
out vec3 fragment_normal;

uniform mat4 model;
uniform mat4 normal_transform;
uniform vec4 color_filter;

void main() {
  	fragment_normal = normalize((normal_transform * vec4(normal, 1.0)).xyz);
  	vec4 model_position = model * vec4(position, 1.0);
	fragment_position = model_position.xyz;
    gl_Position = projection * view * model_position;

	vec3 rgb = process_lights(color, fragment_normal);
    fragment_color = vec4(rgb, color.a) * color_filter;
//    fragment_color = color;
}
