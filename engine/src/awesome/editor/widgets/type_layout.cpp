#include "type_layout.h"

#include "form_layout.h"

void TypeLayout::input(IType& type)
{
	for (const auto& [name, property] : type.type_properties())
	{
		switch (property.type.type)
		{
		case NativeType::Type::T_bool: FormLayout::input(name.c_str(), property.value<bool>(&type)); break;
		case NativeType::Type::T_char: break;
		case NativeType::Type::T_double: FormLayout::input(name.c_str(), property.value<double>(&type)); break;
		case NativeType::Type::T_enum: FormLayout::input(name.c_str(), property.value<bool>(&type)); break;
		case NativeType::Type::T_float: FormLayout::input(name.c_str(), property.value<float>(&type)); break;
		case NativeType::Type::T_int: FormLayout::input(name.c_str(), property.value<int>(&type)); break;
		case NativeType::Type::T_string: FormLayout::input(name.c_str(), property.value<std::string>(&type)); break;
		case NativeType::Type::T_template: 
		{

			break;
		}
		case NativeType::Type::T_type: break;
		default:break;
		}
	}
}
