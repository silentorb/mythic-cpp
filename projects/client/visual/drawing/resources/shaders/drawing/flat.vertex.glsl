
uniform mat4 transform;
uniform vec4 color;

in vec2 position;
in vec4 vertex_color;
out vec4 fragment_color;

void main() {
	fragment_color = color * vertex_color;
	vec4 temp = transform * vec4(position, 0.0, 1.0);
    gl_Position = vec4(temp.x / 500.0 - 1.0, (1000.0 - temp.y) / 500.0 - 1.0, 0.0, 1);
}
