
in vec3 input_position;

uniform mat4 model;

void main() {
	gl_Position = model * vec4(input_position, 1.0);
}
