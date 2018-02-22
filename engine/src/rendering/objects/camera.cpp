#include <awesome/rendering/objects/camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Awesome
{
	namespace Rendering
	{
		Camera* Camera::instance = nullptr;

		Camera::Camera()
		{
			//instances.push_back(this);
			if (instance == nullptr)
				instance = this;

			/* compute projection */
			setType(type, true);
		}

		Camera::Camera(CameraType in_type)
		{
			//instances.push_back(this);
			if (instance == nullptr)
				instance = this;

			/* compute projection */
			setType(in_type, true);
		}

		Camera::~Camera()
		{

		}

		Camera* Camera::main() 
		{
			return instance;
		}

		void Camera::setType(CameraType new_type, bool refresh_projection/* = false*/)
		{
			if (type != new_type || refresh_projection) {
				type = new_type;

				if (type == CameraType::Perspective)
				{
					projection = glm::perspective(fieldOfView, aspectRatio, clippingPlanes.near, clippingPlanes.far);
				}
				else
				{
					// TODO: fix this
					projection = glm::ortho(-4.0f / 3.0f, 4.0f / 3.0f, -1.0f, 1.0f, -1.0f, 1.0f);
				}
			}
		}
	}
}