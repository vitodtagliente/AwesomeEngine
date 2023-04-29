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
		case PropertyType::Type::T_native: break;
		case PropertyType::Type::T_string: FormLayout::input(name.c_str(), property.value<std::string>(&type)); break;
		case PropertyType::Type::T_template: break;
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
