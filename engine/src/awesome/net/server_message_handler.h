/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/core/reflection.h>
#include <awesome/encoding/json.h>

#include "message.h"
#include "user_session.h"

namespace net
{
	class ServerMessageHandler
	{
	public:
		ServerMessageHandler() = default;
		~ServerMessageHandler() = default;

		virtual void execute(UserSession* const userSession, const Message& message) = 0;
	};

	template <typename RequestType, typename ResponseType, 
		typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>,
		typename ResponseEnabled = std::enable_if<std::is_base_of<ISerializable, ResponseType>::value>>
	class ServerComand : public ServerMessageHandler
	{
	public:
		ServerComand() = default;
		~ServerComand() = default;

		virtual void execute(UserSession* const userSession, const Message& message) override
		{
			RequestType request;
			::deserialize(json::Deserializer::parse(message.body.data), request);
			ResponseType response = execute(request);
		}

		REFLECT()

	protected:
		virtual ResponseType execute(const RequestType& request) = 0;
	};

#define REFLECT_SERVER_COMMAND(T) REFLECT_IMP_CATEGORY(T, ServerCommand)
}
