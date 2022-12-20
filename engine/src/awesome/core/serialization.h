/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/sub_type.h>
#include <awesome/core/type_name.h>
#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

struct ISerializable
{
	virtual json::value serialize() const = 0;
	virtual void deserialize(const json::value& value) = 0;
};

struct Serializer
{
	Serializer() = delete;

	static json::value serialize(const Type& type);
	static json::value serialize(const std::shared_ptr<Type>& type);
	static json::value serialize(const std::unique_ptr<Type>& type);
	static json::value serialize(const bool& primitive);
	static json::value serialize(const int& primitive);
	static json::value serialize(const float& primitive);
	static json::value serialize(const double& primitive);
	static json::value serialize(const char& primitive);
	static json::value serialize(const std::string& primitive);
	static json::value serialize(const uuid& id);
	static json::value serialize(const graphics::Color& color);
	static json::value serialize(const graphics::TextureCoords& coords);
	static json::value serialize(const graphics::TextureRect& rect);
	static json::value serialize(const math::transform& t);
	static json::value serialize(const math::vec2& v);
	static json::value serialize(const math::vec3& v);
	static json::value serialize(const math::vec4& v);
	static json::value serialize(const AssetPtr& asset);
	template <typename T = Type>
	static json::value serialize(const TypeName<T>& type)
	{
		return serialize(type.value);
	}
	template <typename T>
	static json::value serialize(const std::vector<T>& list)
	{
		json::value data = json::array();
		for (const auto& element : list)
		{
			data.push_back(serialize(element));
		}
		return data;
	}
	template <typename T>
	static json::value serialize(const std::map<std::string, T>& map)
	{
		json::value data = json::object();
		for (const auto& [name, element] : map)
		{
			data[name] = serialize(element);
		}
		return data;
	}
};

struct Deserializer
{
	Deserializer() = delete;

	static bool deserialize(const json::value& value, Type& type);
	static bool deserialize(const json::value& value, std::shared_ptr<Type>& type);
	static bool deserialize(const json::value& value, std::unique_ptr<Type>& type);
	static bool deserialize(const json::value& value, std::shared_ptr<Type>& type, const std::string& typeName);
	static bool deserialize(const json::value& value, std::unique_ptr<Type>& type, const std::string& typeName);
	static bool deserialize(const json::value& value, bool& primitive);
	static bool deserialize(const json::value& value, int& primitive);
	static bool deserialize(const json::value& value, float& primitive);
	static bool deserialize(const json::value& value, double& primitive);
	static bool deserialize(const json::value& value, char& primitive);
	static bool deserialize(const json::value& value, std::string& primitive);
	static bool deserialize(const json::value& value, uuid& id);
	static bool deserialize(const json::value& value, graphics::Color& color);
	static bool deserialize(const json::value& value, graphics::TextureCoords& coords);
	static bool deserialize(const json::value& value, graphics::TextureRect& rect);
	static bool deserialize(const json::value& value, math::transform& t);
	static bool deserialize(const json::value& value, math::vec2& v);
	static bool deserialize(const json::value& value, math::vec3& v);
	static bool deserialize(const json::value& value, math::vec4& v);
	static bool deserialize(const json::value& value, AssetPtr& asset);
	template <typename T = Type>
	static bool deserialize(const json::value& value, TypeName<T>& type)
	{
		return deserialize(value, type.value);
	}
	template <typename T>
	static bool deserialize(const json::value& value, std::vector<T>& list, const std::function<T()>& createHandler)
	{
		if (!value.is_array()) return false;

		for (const auto& elementValue : value.as_array())
		{
			T element = createHandler();
			if (deserialize(elementValue, element))
			{
				list.push_back(std::move(element));
			}
		}
		return true;
	}
	template <typename T>
	static bool deserialize(const json::value& value, std::vector<T>& list)
	{
		return deserialize<T>(
			value,
			list,
			[]() -> T
			{
				return T();
			}
		);
	}
	static bool deserialize(const json::value& value, std::vector<std::shared_ptr<Type>>& list, const std::string& typeName);
	static bool deserialize(const json::value& value, std::vector<std::unique_ptr<Type>>& list, const std::string& typeName);
	template <typename T>
	static bool deserialize(const json::value& value, std::map<std::string, T>& map, const std::function<T()>& createHandler)
	{
		if (!value.is_object()) return false;

		for (const auto& [name, elementValue] : value.as_object())
		{
			T element = createHandler();
			if (deserialize(elementValue, element))
			{
				map.insert(std::make_pair(name, std::move(element)));
			}
		}
		return true;
	}
	template <typename T>
	static bool deserialize(const json::value& value, std::map<std::string, T>& map)
	{
		return deserialize<T>(
			value,
			map,
			[]() -> T
			{
				return T();
			}
		);
	}
	static bool deserialize(const json::value& value, std::map<std::string, std::shared_ptr<Type>>& map, const std::string& typeName);
	static bool deserialize(const json::value& value, std::map<std::string, std::unique_ptr<Type>>& map, const std::string& typeName);
};