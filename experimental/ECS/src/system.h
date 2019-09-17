#pragma once 

namespace ECS
{
	class ISystem
	{
	public:

		ISystem() = default;
	};

	template <class T>
	class System : public ISystem
	{

	};
}