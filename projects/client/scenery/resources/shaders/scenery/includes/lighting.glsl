
const float constant_attenuation = 0.5;
const float linear_attenuation = 0.2;
const float quadratic_attenuation = 0.05;
const float shininess = 0.9;
const float strength = 0.3;
const vec3 ambient = vec3(0.1, 0.1, 0.1) * 5.0;

struct Relationship {
    vec3 direction;
    float distance;
};

Relationship get_relationship(Light light) {
    Relationship info;
    vec3 light_position = light.position;
	info.direction = vec3(1) - fragment_position;
	info.distance = length(info.direction);

	info.direction = info.direction / info.distance;
	return info;
}

vec3 process_light(Light light, vec4 input_color) {
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

	float diffuse = max(0.0, dot(fragment_normal, camera_direction * 0.8));
	float specular = max(0.0, dot(fragment_normal, half_vector));

	if (diffuse == 0.0)
		specular = 0.0;
	 else
		specular = pow(specular, shininess) * strength;

	//specular = 0;
	vec3 scattered_light = ambient + light.color * diffuse * attenuation;
	vec3 reflected_light = light.color * specular * attenuation;
//	return reflected_light;
	vec3 rgb = min(input_color.rgb * scattered_light + reflected_light, vec3(1.0));
	return rgb;
}

vec3 process_lights(vec4 input_color) {
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
