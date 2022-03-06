/// Copyright (c) Vito Domenico Tagliente

#include <climits>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <type_traits>

#include "typename.h"

typedef std::function<void* ()> factory_constructor_t;

struct TypeFactoryImp
{
	static std::map<const char*, factory_constructor_t>& data()
	{
		static std::map<const char*, factory_constructor_t> s_register;
		return s_register;
	}

	static void hook(const char* name, factory_constructor_t handler)
	{
		data().insert(std::make_pair(name, handler));
	}
};

struct TypeFactory
{
	static void* instantiate(const char* name)
	{
		const auto& it = TypeFactoryImp::data().find(name);
		if (it != TypeFactoryImp::data().end())
		{
			return it->second();
		}
		return nullptr;
	}

	template <typename T>
	static T* instantiate()
	{
		return reinterpret_cast<T*>(instantiate(TypeName<T>::get()));
	}
};

#define REGISTER_TYPE(T) TypeFactoryImp::hook(TypeName<T>::get(), []() -> void* { return new T(); });