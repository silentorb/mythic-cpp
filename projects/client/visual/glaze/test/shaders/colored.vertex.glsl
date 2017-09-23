
uniform mat4 view;
uniform mat4 projection;
uniform vec3 camera_direction;
uniform mat4 model;
uniform mat4 normal_transform;
uniform vec4 color_filter;

struct Light {
	int type;
	float brightness;
	vec3 position;
	vec3 direction;
	vec3 color;
};

const int MAX_LIGHTS = 8;
layout(binding = 2, std140) uniform struct _Lightingness {
	Light lights[MAX_LIGHTS];
	int count;
} Lighting;

const float constant_attenuation = 0.5;
const float linear_attenuation = 0.2;
const float quadratic_attenuation = 0.05;
const float shininess = 0.9;
const float strength = 0.3;
//const vec3 ambient = vec3(0.5);
const vec3 ambient = vec3(0.7);

struct Relationship {
    vec3 direction;
    float distance;
};

Relationship get_relationship(Light light) {
    Relationship info;
//	info.direction = normalize(light.position - position);
	info.direction = normalize(vec3(-1, 0, 0));
	info.distance = length(info.direction);
	return info;
}

vec3 process_light(Light light, vec4 input_color, vec3 normal) {
	Relationship info = get_relationship(light);

	float attenuation = 1.5;
	vec3 half_vector = normalize(info.direction + camera_direction);

	float diffuse = max(0.0, dot(normal, info.direction * 1.0));
	float specular = max(0.0, dot(normal, half_vector));
//	diffuse = diffuse > 0.01 ? 2.0 : 0.5;

	if (diffuse == 0.0)
		specular = 0.0;
	 else
		specular = pow(specular, shininess) * strength;

	//specular = 0;
	vec3 scattered_light = ambient + light.color * diffuse * attenuation;
	vec3 reflected_light = light.color * specular * attenuation;
	reflected_light = vec3(0);
//	return scattered_light;
	vec3 rgb = min(input_color.rgb * scattered_light + reflected_light, vec3(1.0));
	return rgb;
}

vec3 process_lights(vec4 input_color, vec3 normal) {
	vec3 result = vec3(0);
	for(int i = 0; i < Lighting.count; ++i) {
//		result += process_light(Lighting.lights[i], input_color, normal);
	}

	Light light;
	light.type = 0;
	light.brightness = 1.0;
	light.position = vec3(-1000, 0, 0);
	light.direction = vec3(0);
	light.color = vec3(1);
	result += process_light(light, input_color, normal);

	return min(result, vec3(1.0));
}

in vec3 position;
in vec3 normal;
in vec4 color;

out vec4 fragment_color;
out vec3 fragment_position;
out vec3 fragment_normal;

void main() {
  	fragment_normal = normalize((normal_transform * vec4(normal, 1.0)).xyz);
  	vec4 model_position = model * vec4(position, 1.0);
	fragment_position = model_position.xyz;
    gl_Position = projection * view * model_position;

	vec3 rgb = process_lights(color, fragment_normal);
    fragment_color = vec4(rgb, color.a) * color_filter;
//    fragment_color = color;
}
