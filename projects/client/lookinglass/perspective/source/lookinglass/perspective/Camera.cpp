#include "Camera.h"
#include <glm/gtx/transform.hpp>
#include "logger.h"

namespace lookinglass {
	namespace perspective {

		mat4 Camera::get_view_matrix() {
//			auto translation = glm::translate(position);
//			auto rotation = glm::mat4_cast(orientation);
//			auto first = translation * rotation;
//			auto second = translation * glm::inverse(rotation);
//			auto third = glm::inverse(rotation) * translation;
//			auto fourth = glm::lookAt(position, vec3(0), vec3(0, 0, 1));
//			return translation * glm::inverse(rotation);
//			log_info("orientation a");
			auto forward = vec3(0, 1, 0) * orientation;
//			log_info("orientation b");
//			auto forward = Vector3.Transform(new Vector3(0, 1, 0), target_transform.Rotation);
			auto look_at = position + forward;
			return glm::lookAt(position, look_at, vec3(0, 0, 1));
//			return result;
//			return glm::lookAt(position, vec3(0), vec3(0, 0, 1));




//			auto result= glm::translate(vec3(0, -10, 0));
//			return result;
		}
	}
}