
in vec4 fragment_color;
in vec3 fragment_position;
in vec3 fragment_normal;

out vec4 output_color;

#include <scenery/includes/scene>
#include <space/includes/lighting>

void main() {
//	vec3 rgb = process_lights(fragment_color, fragment_normal);
//	output_color = vec4(rgb, fragment_color.a);
	output_color = fragment_color;
}
