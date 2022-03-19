/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <map>

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

struct TypeDescriptor
{
	TypeDescriptor(std::function<void(TypeDescriptor*)> init)
		: name()
		, size()
	{
		init(this);
	}

	template<typename T>
	static const TypeDescriptor& get()
	{
		return T::s_typeDescriptor;
	}

	const char* name;
	size_t size;
};

struct TypeFactory
{
	static void* instantiate(const char* name)
	{
		const std::map<const char*, factory_constructor_t>& constructors = TypeFactoryImp::data();
		const auto& it = constructors.find(name);
		if (it != constructors.end())
		{
			return it->second();
		}
		return nullptr;
	}

	template <typename T>
	static T* instantiate()
	{
		return reinterpret_cast<T*>(instantiate(TypeDescriptor::get<T>().name));
	}

	template <typename T>
	static T* instantiate(const char* name)
	{
		return reinterpret_cast<T*>(instantiate(name));
	}
};

#define REFLECT() \
public: \
	friend struct TypeDescriptor; \
	virtual const TypeDescriptor& getTypeDescriptor() const; \
private: \
    static TypeDescriptor s_typeDescriptor; \
    static void registerTypeDescriptor(TypeDescriptor*); 

#define REFLECT_IMP(T) \
    TypeDescriptor T::s_typeDescriptor{T::registerTypeDescriptor}; \
    \
    void T::registerTypeDescriptor(TypeDescriptor* descriptor) \
    { \
        descriptor->name = #T; \
        descriptor->size = sizeof(T); \
        \
        TypeFactoryImp::hook(#T, []() -> void* { return new T(); }); \
    } \
	\
	const TypeDescriptor& T::getTypeDescriptor() const \
	{ \
		return T::s_typeDescriptor; \
	}

#define REFLECT_IMP_ALIAS(T, N) \
    TypeDescriptor T::s_typeDescriptor{T::registerTypeDescriptor}; \
    \
    void T::registerTypeDescriptor(TypeDescriptor* descriptor) \
    { \
        descriptor->name = N; \
        descriptor->size = sizeof(T); \
        \
        TypeFactoryImp::hook(#T, []() -> void* { return new T(); }); \
    } \
	\
	const TypeDescriptor& T::getTypeDescriptor() const \
	{ \
		return T::s_typeDescriptor; \
	}