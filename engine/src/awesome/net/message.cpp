#include "message.h"

namespace net
{
	json::value Message::serialize() const
	{
		return json::object({
			{"id", ::serialize(id)},
			{"reliable", reliable},
			{"type", type},
			{"data", data},
			});
	}

	void Message::deserialize(const json::value& value)
	{
		::deserialize(value.safeAt("id"), id);
		reliable = value.safeAt("reliable").as_bool(false);
		type = value.safeAt("type").as_string();
		data = value.safeAt("data").as_string();
	}
}