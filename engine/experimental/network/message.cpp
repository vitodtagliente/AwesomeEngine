#include "message.h"

namespace net
{
	json::value Message::serialize() const
	{
		return json::object({
			{"id", Serializer::serialize(header.id)},
			{"version", header.version},
			{"commandId", header.commandId},
			{"commandPhase", enumToString(header.commandPhase)},
			{"data", body.data},
			});
	}

	void Message::deserialize(const json::value& value)
	{
		Deserializer::deserialize(value.safeAt("id"), header.id);
		header.version = value.safeAt("version").as_number(0.1).as_double();
		header.commandId = value.safeAt("commandId").as_string("");
		stringToEnum(value.safeAt("commandPhase").as_string(""), header.commandPhase);
		body.data = value.safeAt("data");
	}
}