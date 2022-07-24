/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/core/reflection.h>
#include <awesome/encoding/json.h>

#include "message.h"

namespace net
{
	class IClientCommand
	{
	public:
		IClientCommand() = default;
		virtual ~IClientCommand() = default;

		virtual void execute(const Message& message) = 0;
	};

	typedef std::unique_ptr<IClientCommand> ClientCommandPtr;

	template <typename RequestType, typename ResponseType,
	typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>,
	typename ResponseEnabled = std::enable_if<std::is_base_of<ISerializable, ResponseType>::value>>
	class ClientCommand : public IClientCommand
	{
	public:
		ClientCommand() = default;
		virtual ~ClientCommand() = default;

		virtual void execute(const Message& message) override
		{
			RequestType request;
			request.deserialize(json::Deserializer::parse(message.body.data));
			ResponseType response = execute(request);
		}

	protected:
		virtual ResponseType execute(const RequestType& request) = 0;
	};

	template <typename RequestType, typename RequestEnabled = std::enable_if<std::is_base_of<ISerializable, RequestType>::value>>
	class ClientCommandNoResponse : public IClientCommand
	{
	public:
		ClientCommandNoResponse() = default;
		virtual ~ClientCommandNoResponse() = default;

		virtual void execute(const Message& message) override
		{
			RequestType request;
			request.deserialize(json::Deserializer::parse(message.body.data));
			execute(request);
		}

	protected:
		virtual void execute(const RequestType& request) = 0;
	};

#define REFLECT_CLIENT_COMMAND(T) REFLECT_IMP_CATEGORY(T, ClientCommand)
}
