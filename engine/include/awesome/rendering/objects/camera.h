#pragma once

#include "../../object.h"

namespace Awesome
{
	enum CameraType
	{
		Orthographic,
		Perspective
	};

	class Camera : public Object
	{
	private:
		static Camera* instance;

		glm::mat4 projection{ 1.0f };
			
		CameraType type{ CameraType::Perspective };
			
	public:
		Camera();
		Camera(CameraType camera_type);
		~Camera();

		static Camera* main();

		float fieldOfView{ 60.0f };
		float aspectRatio{ 1.33f };
		float clipping_near{ 0.1f };
		float clipping_far{ 100.0f };

		glm::vec4 background{ 0.2f, 0.25f, 0.3f, 1.0f };

		void setType(CameraType new_type, bool refresh_projection = false);

		CameraType getType() const { return type; }

		glm::mat4 getProjection() const { return projection; }
		glm::mat4 getView() const;
			
		static void clear();
	};

	class PerspectiveCamera : public Camera
	{
		PerspectiveCamera() : Camera(CameraType::Perspective) {}
	};

	class OrthographicCamera : public Camera
	{
		OrthographicCamera() : Camera(CameraType::Orthographic) {}
	};
}