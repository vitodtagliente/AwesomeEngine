#include "type_serialization.h"

#include "serialization.h"

json::value Serializer<IType>::serialize(const IType& value)
{
	return json::value();
}

bool Serializer<IType>::deserialize(const json::value& data, IType& value)
{
	return false;
}

json::value Serializer<std::vector<IType>>::serialize(const std::vector<IType>& value)
{
	return json::value();
}

bool Serializer<std::vector<IType>>::deserialize(const json::value& data, std::vector<IType>& value)
{
	return false;
}

json::value Serializer<std::vector<std::unique_ptr<IType>>>::serialize(const std::vector<std::unique_ptr<IType>>& value)
{
	return json::value();
}

bool Serializer<std::vector<std::unique_ptr<IType>>>::deserialize(const json::value& data, std::vector<std::unique_ptr<IType>>& value)
{
	return false;
}