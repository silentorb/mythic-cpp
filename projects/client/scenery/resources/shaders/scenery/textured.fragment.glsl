
//#include <scene>

in vec2 texture_coordinates;
//in vec3 normal;
//in vec3 position;

out vec4 output_color;

uniform sampler2D current_texture;

//#include <lighting>

void main() {
	vec4 color = texture(current_texture, texture_coordinates);
//	vec3 rgb = process_lights(color);
    output_color = vec4(rgb, color.a);
}
