#include "update_world_command.h"

#include <awesome/entity/world.h>

namespace net
{
	namespace command
	{
		json::value UpdateWorldRequest::serialize() const
		{
			return data;
		}

		void UpdateWorldRequest::deserialize(const json::value& value)
		{
			data = value;
		}

		void UpdateWorldCommand::execute(const UpdateWorldRequest& request)
		{
			World::instance().netDeserialize(request.data);
		}

		REFLECT_CLIENT_COMMAND(UpdateWorldCommand)
	}
}