uniform 	mat4 view;
uniform 	mat4 projection;
uniform 	vec3 camera_direction;

struct Light {
	int type;
	float brightness;
	vec3 position;
	vec3 direction;
	vec3 color;
};

const int MAX_LIGHTS = 8;
layout(binding = 2, std140) uniform struct Lightingness{
	int count;
	Light lights[MAX_LIGHTS];
} Lighting;