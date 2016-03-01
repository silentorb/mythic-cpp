
uniform mat4 transform;
uniform vec4 color;
uniform vec2 scaling;

in vec2 position;
out vec4 fragment_color;

void main() {
	fragment_color = color;
	vec4 temp = transform * vec4(position * scaling, 0.0, 1.0);
    gl_Position = vec4(temp.x / 500 - 1, (1000 - temp.y) / 500 - 1, 0.0, 1);
//    gl_Position = vec4(temp.x / 500 - 1, temp.y/ 500 + 0.5, 0.0, 1);
}
