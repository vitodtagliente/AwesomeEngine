#include "message.h"

namespace net
{
	static const std::string s_key{ "awesome" };

	std::string encrypt(const std::string& data, const std::string& key)
	{
		if (key.empty())
			return data;

		std::string msg(data);
		for (std::string::size_type i = 0; i < data.size(); ++i)
			msg[i] ^= key[i % key.size()];
		return msg;
	}

	json::value Message::serialize() const
	{
		return json::object({
			{"id", ::serialize(header.id)},
			{"version", header.version},
			{"commandId", header.commandId},
			{"data", encrypt(body.data, s_key)},
			});
	}

	void Message::deserialize(const json::value& value)
	{
		::deserialize(value.safeAt("id"), header.id);
		header.version = value.safeAt("version").as_number(0.1).as_double();
		header.commandId = value.safeAt("commandId").as_string("");
		body.data = encrypt(value.safeAt("data").as_string(""), s_key);
	}
}