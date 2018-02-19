#pragma once

#include "../../scenegraph/object.h"
#include <vector>
#include <glm/vec4.hpp>

namespace Awesome
{
	namespace Rendering
	{
		enum CameraProjection
		{
			Orthographic,
			Perspective
		};

		class Camera : public Scenegraph::Object
		{
		private:
			static std::vector<Camera*> instances;
			static Camera* instance;

		public:
			Camera();
			~Camera();

			static Camera* main();

			CameraProjection projection{ CameraProjection::Perspective };
			float fieldOfView{ 60.0f };
			float near{ 0.3f };
			float far{ 1000.0f };

			glm::vec4 background{ 0.2f, 0.25f, 0.3f, 1.0f };
		};
	}
}