#include "message.h"

namespace net
{
	json::value Message::serialize() const
	{
		return json::object({
			{"id", ::serialize(header.id)},
			{"version", header.version},
			{"commandId", header.commandId},
			{"data", body.data},
			});
	}

	void Message::deserialize(const json::value& value)
	{
		::deserialize(value.safeAt("id"), header.id);
		header.version = value.safeAt("version").as_number(0.1).as_double();
		header.commandId = value.safeAt("commandId").as_string("");
		body.data = value.safeAt("data").as_string("");
	}
}