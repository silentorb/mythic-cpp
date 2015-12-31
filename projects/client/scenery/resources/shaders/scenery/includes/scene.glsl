layout(binding = 1) uniform Scene{
	mat4 view;
	mat4 projection;
	vec3 camera_direction;
} scene;

struct Light {
	int type;
	float brightness;
	vec3 position;
	vec3 direction;
	vec3 color;
};

const int MAX_LIGHTS = 8;
layout(binding = 2, std140) uniform Lightingness{
	int count;
	Light lights[MAX_LIGHTS];
} Lighting;