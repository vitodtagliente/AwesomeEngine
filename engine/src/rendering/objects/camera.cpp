#include <awesome/rendering/objects/camera.h>
#include <awesome/rendering/context.h>
#include <awesome/math/math.h>
#include <awesome/application.h>

namespace Awesome
{
	Camera* Camera::instance = nullptr;

	Camera* Camera::main() 
	{
		if (instance == nullptr)
		{
			instance = Application::instance()->getScene()->findObject<Camera>();
		}
		return instance;
	}

	void Camera::setType(CameraType new_type, bool refresh_projection/* = false*/)
	{
		if (type != new_type || refresh_projection) {
			type = new_type;

			if (type == CameraType::Perspective)
			{
				projection = glm::perspective<float>(fieldOfView, aspectRatio, clipping_near, clipping_far);
			}
			else
			{
				// TODO: fix this
				projection = glm::ortho(-4.0f / 3.0f, 4.0f / 3.0f, -1.0f, 1.0f, -1.0f, 1.0f);
			}
		}
	}

	void Camera::init()
	{
		name = "camera";
		if (instance == nullptr)
			instance = this;

		Object::init();
		setType(type);
	}

	glm::mat4 Camera::getView() const
	{
		return transform.getHierarchy();
	}
		
	void Camera::clear()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClear(GL_COLOR_BUFFER_BIT);
		if (instance != nullptr)
		{
			glClearColor(instance->background.r, instance->background.g, 
				instance->background.b, instance->background.a);
		}
		else
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	}
}