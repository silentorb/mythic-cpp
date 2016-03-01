
uniform mat4 projection;
uniform mat4 model;
uniform vec4 color;

in vec3 position;
out vec4 fragment_color;

void main() {
	fragment_color = color;
    gl_Position = projection * model * vec4(position, 1.0);
}
