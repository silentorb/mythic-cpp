#include "Camera.h"
#include <glm/gtx/transform.hpp>

namespace lookinglass {
	namespace perspective {

		mat4 Camera::get_view_matrix() {
			auto translation = glm::translate(position);
			auto rotation = glm::mat4_cast(orientation);
			auto first = translation * rotation;
			auto second = translation * glm::inverse(rotation);
			auto third = glm::inverse(rotation) * translation;
			auto fourth = glm::lookAt(position, vec3(0), vec3(0, 0, 1));
//			return translation * glm::inverse(rotation);
			auto forward = orientation * vec3(0, 1, 0);
//			auto forward = Vector3.Transform(new Vector3(0, 1, 0), target_transform.Rotation);
			auto look_at = position + forward;
//			auto result = glm::lookAt(position, look_at, vec3(0, 0, 1));
//			return result;
			return glm::lookAt(position, vec3(0), vec3(0, 0, 1));
		}
	}
}