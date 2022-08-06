#include "uuid_serializer.h"

#include <awesome/core/uuid.h>

bool UuidSerializer::canSerialize(const FieldDescriptor& field)
{
	return field.typeStr == "uuid"
		;
}
json::value UuidSerializer::serialize(const FieldDescriptor& field)
{
	return static_cast<std::string>(field.value<uuid>());
}

bool UuidSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	field.value<uuid>() = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	return true;
}
