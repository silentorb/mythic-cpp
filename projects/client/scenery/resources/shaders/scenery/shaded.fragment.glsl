
#include <scene>

in vec3 normal;
in vec3 position;

out vec4 output_color;
uniform vec4 color;

#include <lighting>

void main() {
	vec3 rgb = process_lights(color);
    output_color = vec4(rgb, color.a);
}
