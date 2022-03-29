/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <map>
#include <set>
#include <typeinfo>

typedef std::function<void* ()> factory_constructor_t;

struct TypeFactoryImp
{
	static std::map<std::string, factory_constructor_t>& data()
	{
		static std::map<std::string, factory_constructor_t> s_register;
		return s_register;
	}

	static std::map<std::string, std::set<std::string>>& categories()
	{
		static std::map<std::string, std::set<std::string>> s_categories;
		return s_categories;
	}

	static void hook(const std::string& name, const std::string& category, factory_constructor_t handler)
	{
		data().insert(std::make_pair(name, handler));

		const auto& it = categories().find(category);
		if (it != categories().end())
		{
			it->second.insert(name);
		}
		else
		{
			categories().insert(std::make_pair(category, std::set<std::string>{ name }));
		}
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

	std::string name;
	size_t size;
};

struct TypeFactory
{
	static void* instantiate(const std::string& name)
	{
		const std::map<std::string, factory_constructor_t>& constructors = TypeFactoryImp::data();
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
	static T* instantiate(const std::string& name)
	{
		return reinterpret_cast<T*>(instantiate(name));
	}

	static std::set<std::string> listByCategory(const std::string& category)
	{
		const std::map<std::string, std::set<std::string>>& categories = TypeFactoryImp::categories();
		const auto& it = categories.find(category);
		if (it != categories.end())
		{
			return it->second;
		}
		return {};
	}

	template <typename T>
	static void load()
	{
		TypeDescriptor::get<T>();
	}
};

#define REFLECT() \
public: \
	friend struct TypeDescriptor; \
	virtual const TypeDescriptor& getTypeDescriptor() const; \
private: \
    static TypeDescriptor s_typeDescriptor; \
    static void registerTypeDescriptor(TypeDescriptor*); 

#define REFLECT_IMP_CATEGORY(T, C) \
    TypeDescriptor T::s_typeDescriptor{T::registerTypeDescriptor}; \
    \
    void T::registerTypeDescriptor(TypeDescriptor* descriptor) \
    { \
        descriptor->name = #T; \
        descriptor->size = sizeof(T); \
        \
        TypeFactoryImp::hook(#T, #C, []() -> void* { return new T(); }); \
    } \
	\
	const TypeDescriptor& T::getTypeDescriptor() const \
	{ \
		return T::s_typeDescriptor; \
	}

#define REFLECT_IMP(T) REFLECT_IMP_CATEGORY(T, Default)

#define REFLECT_IMP_CATEGORY_ALIAS(T, C, N) \
    TypeDescriptor T::s_typeDescriptor{T::registerTypeDescriptor}; \
    \
    void T::registerTypeDescriptor(TypeDescriptor* descriptor) \
    { \
        descriptor->name = N; \
        descriptor->size = sizeof(T); \
        \
        TypeFactoryImp::hook(#T, #C, []() -> void* { return new T(); }); \
    } \
	\
	const TypeDescriptor& T::getTypeDescriptor() const \
	{ \
		return T::s_typeDescriptor; \
	}

#define REFLECT_IMP_ALIAS(T, C, N) REFLECT_IMP_CATEGORY_ALIAS(T, Default, N)

#define REFLECT_COMPONENT(T) REFLECT_IMP_CATEGORY(T, Component)
#define REFLECT_EDITOR(T) REFLECT_IMP_CATEGORY(T, Editor)