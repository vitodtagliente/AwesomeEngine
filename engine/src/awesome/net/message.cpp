#include "message.h"

namespace net
{
	json::value Message::serialize() const
	{
		Serializer serializer;
		return json::object({
			{"id", serializer.serialize(header.id)},
			{"version", header.version},
			{"commandId", header.commandId},
			{"commandPhase", enumToString(header.commandPhase)},
			{"data", body.data},
			});
	}

	void Message::deserialize(const json::value& value)
	{
		Deserializer deserializer;
		deserializer.deserialize(value.safeAt("id"), header.id);
		header.version = value.safeAt("version").as_number(0.1).as_double();
		header.commandId = value.safeAt("commandId").as_string("");
		stringToEnum(value.safeAt("commandPhase").as_string(""), header.commandPhase);
		body.data = value.safeAt("data");
	}
}