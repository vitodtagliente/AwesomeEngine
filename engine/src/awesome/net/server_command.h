/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/core/reflection.h>
#include <awesome/encoding/json.h>

#include "message.h"
#include "user_session.h"

namespace net
{
	class IServerCommand
	{
	public:
		IServerCommand() = default;
		virtual ~IServerCommand() = default;

		virtual void execute(UserSession* const userSession, const Message& message) = 0;
		virtual bool requireAuthentication() const { return false; }
	};

	typedef std::unique_ptr<IServerCommand> ServerCommandPtr;

	template <typename RequestType, typename ResponseType,
		typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>,
		typename ResponseEnabled = std::enable_if<std::is_base_of<ISerializable, ResponseType>::value>>
		class ServerCommand : public IServerCommand
	{
	public:
		ServerCommand() = default;
		virtual ~ServerCommand() = default;

		virtual void execute(UserSession* const userSession, const Message& message) override
		{
			RequestType request;
			request.deserialize(json::Deserializer::parse(message.body.data));
			ResponseType response = execute(request);
		}

	protected:
		virtual ResponseType execute(const RequestType& request) = 0;
	};

	template <typename RequestType, typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>>
	class ServerCommandNoResponse : public IServerCommand
	{
	public:
		ServerCommandNoResponse() = default;
		virtual ~ServerCommandNoResponse() = default;

		virtual void execute(UserSession* const userSession, const Message& message) override
		{
			RequestType request;
			request.deserialize(json::Deserializer::parse(message.body.data));
			execute(userSession, request);
		}

	protected:
		virtual void execute(UserSession* const userSession, const RequestType& request) = 0;
	};
}

#define REFLECT_SERVER_COMMAND(T) REFLECT_IMP_CATEGORY(T, ServerCommand)
