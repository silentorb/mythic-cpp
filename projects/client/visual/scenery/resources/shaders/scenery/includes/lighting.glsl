struct Light {
	int type;
	float brightness;
	vec3 position;
	vec3 direction;
	vec3 color;
};

const float constant_attenuation = 0.5;
const float linear_attenuation = 0.2;
const float quadratic_attenuation = 0.05;
const float shininess = 0.9;
const float strength = 0.3;
const vec3 ambient = vec3(0.1);

struct Relationship {
    vec3 direction;
    float distance;
};

Relationship get_relationship(Light light) {
    Relationship info;
	info.direction = normalize(light.position - fragment_position);
	info.distance = length(info.direction);

//	info.direction = info.direction / info.distance;
	return info;
}

vec3 process_light(Light light, vec4 input_color, vec3 camera_direction) {
	Relationship info = get_relationship(light);

	float attenuation;
	if (light.type == 0) {
		attenuation = 1.0;
	}
	else {
		attenuation = 1.0 /
			(
	//		constant_attenuation + 
			linear_attenuation * info.distance
	//		quadratic_attenuation * light_distance * light_distance
			);
	}

	vec3 half_vector = normalize(info.direction + camera_direction);

	float diffuse = max(0.0, dot(fragment_normal, info.direction * 0.8));
	float specular = max(0.0, dot(fragment_normal, half_vector));
//	diffuse = diffuse > 0.1 ? 2 : 0;

	if (diffuse == 0.0)
		specular = 0.0;
	 else
		specular = pow(specular, shininess) * strength;

	//specular = 0;
	vec3 scattered_light = ambient + light.color * diffuse * attenuation;
	vec3 reflected_light = light.color * specular * attenuation;
//	return scattered_light;
	vec3 rgb = min(input_color.rgb * scattered_light + reflected_light, vec3(1.0));
	return rgb;
}

vec3 process_lights(vec4 input_color, vec3 camera_direction) {
	vec3 result = vec3(0);
	for(int i = 0; i < Lighting.count; ++i) {
		result += process_light(Lighting.lights[i], input_color);
	}

	Light light;
	light.type = 0;
	light.brightness = 1.0;
	light.position = vec3(-1000, 0, 0);
	light.direction = vec3(0);
	light.color = vec3(1);
	result += process_light(light, input_color);

	return min(result, vec3(1.0));
}
