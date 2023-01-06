/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/encoding/json.h>

#include "command_error.h"
#include "connection.h"
#include "message.h"
#include "user_session.h"

namespace net
{
	class IServerCommand
	{
	public:
		IServerCommand() = default;
		virtual ~IServerCommand() = default;

		virtual CommandError execute(Connection* const connection, UserSession* const userSession, const Message& message) = 0;
		virtual bool requireAuthentication() const { return false; }
	};

	typedef std::unique_ptr<IServerCommand> ServerCommandPtr;

	template <
		typename RequestType, 
		typename ResponseType,
		typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>,
		typename ResponseEnabled = std::enable_if<std::is_base_of<ISerializable, ResponseType>::value>
	>
	class ServerCommand : public IServerCommand
	{
	public:
		ServerCommand() = default;
		virtual ~ServerCommand() = default;

		virtual CommandError execute(Connection* const connection, UserSession* const userSession, const Message& message) override
		{
			RequestType request;
			request.deserialize(message.body.data);
			ResponseType response;
			CommandError error = execute(userSession, request, response);

			Message responseMessage;
			responseMessage.header.id = message.header.id;
			responseMessage.header.commandId = message.header.commandId;
			responseMessage.header.commandPhase = CommandPhase::Response;
			responseMessage.body.data = response.serialize();

			connection->send(userSession->getAddress(), responseMessage);

			return error;
		}

	protected:
		virtual CommandError execute(UserSession* const userSession, const RequestType& request, ResponseType& response) = 0;
	};

	template <
		typename RequestType, 
		typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>
	>
	class ServerCommandNoResponse : public IServerCommand
	{
	public:
		ServerCommandNoResponse() = default;
		virtual ~ServerCommandNoResponse() = default;

		virtual CommandError execute(Connection* const, UserSession* const userSession, const Message& message) override
		{
			RequestType request;
			request.deserialize(message.body.data);
			return execute(userSession, request);
		}

	protected:
		virtual CommandError execute(UserSession* const userSession, const RequestType& request) = 0;
	};
}
