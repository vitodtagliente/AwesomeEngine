#include <awesome/rendering/objects/camera.h>

namespace Awesome
{
	namespace Rendering
	{
		Camera* instance = nullptr;

		Camera::Camera()
		{
			instances.push_back(this);
		}

		Camera::~Camera()
		{

		}

		Camera* Camera::main() 
		{
			return instance;
		}
	}
}