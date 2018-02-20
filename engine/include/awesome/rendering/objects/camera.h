#pragma once

#include "../../scenegraph/object.h"
#include <vector>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

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
			Camera(CameraType in_type);
			~Camera();

			static Camera* main();

			float fieldOfView{ 60.0f };
			float aspectRatio{ 1.33f }; /* 4:3 */
			float near{ 0.1f };
			float far{ 100.0f };

			glm::vec4 background{ 0.2f, 0.25f, 0.3f, 1.0f };

			void setType(CameraType new_type, bool refresh_projection = false);

			CameraType getType() const { return type; }

			glm::mat4 getProjection() const { return projection; }
			glm::mat4 getView() const { return transform.get(); }
		};
	}
}