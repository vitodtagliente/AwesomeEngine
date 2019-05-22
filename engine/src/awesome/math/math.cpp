#include "math.h"

namespace awesome
{
	namespace math
	{
		float radians(const float t_theta)
		{
			return t_theta * deg2rad_factor;
		}

		// radians to degrees
		float degrees(const float t_theta)
		{
			return t_theta * rad2deg_factor;
		}
	}
}