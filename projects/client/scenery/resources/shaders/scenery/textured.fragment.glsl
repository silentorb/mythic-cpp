
#include <scene>

in vec2 texture_coordinates;
in vec3 normal;
in vec3 position;

out vec4 output_color;

uniform sampler2D current_texture;

#include <lighting>

void main() {
	vec4 color = texture(current_texture, texture_coordinates);
	vec3 rgb = process_lights(color);
    //output_color = vec4(vec3(Lighting.lights[0].type), color.a);
    //output_color = vec4(vec3(Lighting.lights[0].brightness), color.a);
    //output_color = vec4(vec3(Lighting.lights[0].direction.x), color.a);
	//output_color = vec4(vec3(Lighting.count), color.a);
    output_color = vec4(rgb, color.a);
}
