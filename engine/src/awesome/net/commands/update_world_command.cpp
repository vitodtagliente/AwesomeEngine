#include "update_world_command.h"

#include <awesome/entity/world.h>

namespace net
{
	namespace command
	{
		json::value UpdateWorldRequest::serialize() const
		{
			return json::object({
				{"data", data}
				});
		}

		void UpdateWorldRequest::deserialize(const json::value& value)
		{
			data = value.safeAt("data").as_string("");
		}

		void UpdateWorldCommand::execute(const UpdateWorldRequest& request)
		{
			json::value data = json::Deserializer::parse(request.data);
			World::instance().netDeserialize(data);
		}

		REFLECT_CLIENT_COMMAND(UpdateWorldCommand)
	}
}