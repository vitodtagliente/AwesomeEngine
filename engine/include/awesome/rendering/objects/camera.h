#pragma once

#include "../../scenegraph/object.h"

namespace Awesome
{
	namespace Rendering
	{
		enum CameraType
		{
			Orthographic,
			Perspective
		};

		class Camera : public Scenegraph::Object
		{
		private:
			//static std::vector<Camera*> instances;
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
			
			struct ClippingPlanes {
				float near{ 0.1f };
				float far{ 100.0f };
			} clippingPlanes;

			glm::vec4 background{ 0.2f, 0.25f, 0.3f, 1.0f };

			void setType(CameraType new_type, bool refresh_projection = false);

			CameraType getType() const { return type; }

			glm::mat4 getProjection() const { return projection; }
			glm::mat4 getView() const;

			void clearScreen();
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
}