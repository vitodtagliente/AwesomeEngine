#include "type_layout.h"

#include "form_layout.h"

void TypeLayout::input(IType& type)
{
	for (const auto& [name, property] : type.type_properties())
	{
		switch (property.type.type)
		{
		case PropertyType::Type::T_bool: FormLayout::input(name.c_str(), property.value<bool>(&type)); break;
		case PropertyType::Type::T_char: break;
		case PropertyType::Type::T_double: FormLayout::input(name.c_str(), property.value<double>(&type)); break;
		case PropertyType::Type::T_enum: FormLayout::input(name.c_str(), property.value<bool>(&type)); break;
		case PropertyType::Type::T_float: FormLayout::input(name.c_str(), property.value<float>(&type)); break;
		case PropertyType::Type::T_int: FormLayout::input(name.c_str(), property.value<int>(&type)); break;
		case PropertyType::Type::T_native: 
		{
			if (property.type.name == reflect::Type<graphics::Color>::name())
			{
				FormLayout::input(name.c_str(), property.value<graphics::Color>(&type));
			}
			else if (property.type.name == reflect::Type<graphics::TextureCoords>::name())
			{
				FormLayout::input(name.c_str(), property.value<graphics::TextureCoords>(&type));
			}
			else if (property.type.name == reflect::Type<graphics::TextureRect>::name())
			{
				FormLayout::input(name.c_str(), property.value<graphics::TextureRect>(&type));
			}
			else if (property.type.name == reflect::Type<math::transform>::name())
			{
				FormLayout::input(name.c_str(), property.value<math::transform>(&type));
			}
			else if (property.type.name == reflect::Type<math::vec2>::name())
			{
				FormLayout::input(name.c_str(), property.value<math::vec2>(&type));
			}
			else if (property.type.name == reflect::Type<math::vec3>::name())
			{
				FormLayout::input(name.c_str(), property.value<math::vec3>(&type));
			}
			else if (property.type.name == reflect::Type<math::vec4>::name())
			{
				FormLayout::input(name.c_str(), property.value<math::vec4>(&type));
			}
			break;
		}
		case PropertyType::Type::T_string: FormLayout::input(name.c_str(), property.value<std::string>(&type)); break;
		case PropertyType::Type::T_template: 
		{
			if ((property.type.name == "std::vector" || property.type.name == "vector") && property.type.children.front().type == PropertyType::Type::T_type)
			{
				// const std::string& typeName = property.type.children.front().name;
				// auto& list = property.value<std::vector<IType>&>(&type);
				
			}
			break;
		}
		case PropertyType::Type::T_type: 
		{
			for (const auto& [type_name, options] : TypeFactory::list("Type", "Asset"))
			{
				if (type_name == property.type.name)
				{
					FormLayout::asset(name.c_str(), property.value<Asset>(&type)); 
					break;
				}
			}
			break;
		}
		default:break;
		}
	}
}
