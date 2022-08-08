#include "commands.h"

namespace net
{
namespace command
{
const TypeDescriptor& ConnectCommand::get_descriptor() const
{
    return ConnectCommandType::descriptor();
}

fields_t ConnectCommand::get_fields() const
{
    return ConnectCommandType::fields(this);
}

void ConnectCommand::autoload()
{
    TypeFactory::load<ConnectCommand>();
}

const TypeDescriptor& ConnectCommand::descriptor()
{
    return ConnectCommandType::descriptor();
}

TypeDescriptor ConnectCommandType::s_typeDescriptor{ ConnectCommandType::registerTypeDescriptor };

const TypeDescriptor& ConnectCommandType::descriptor()
{
    return s_typeDescriptor;
}

fields_t ConnectCommandType::fields(const ConnectCommand* const)
{
    return fields_t();
}

void ConnectCommandType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "ConnectCommand";
    descriptor->size = sizeof(ConnectCommand);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Command"));

    TypeFactoryRegister::hook("ConnectCommand", []() -> const TypeDescriptor& { return ConnectCommandType::s_typeDescriptor; }, []() -> void* { return new ConnectCommand(); });
}

const TypeDescriptor& DisconnectCommand::get_descriptor() const
{
    return DisconnectCommandType::descriptor();
}

fields_t DisconnectCommand::get_fields() const
{
    return DisconnectCommandType::fields(this);
}

void DisconnectCommand::autoload()
{
    TypeFactory::load<DisconnectCommand>();
}

const TypeDescriptor& DisconnectCommand::descriptor()
{
    return DisconnectCommandType::descriptor();
}

TypeDescriptor DisconnectCommandType::s_typeDescriptor{ DisconnectCommandType::registerTypeDescriptor };

const TypeDescriptor& DisconnectCommandType::descriptor()
{
    return s_typeDescriptor;
}

fields_t DisconnectCommandType::fields(const DisconnectCommand* const)
{
    return fields_t();
}

void DisconnectCommandType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "DisconnectCommand";
    descriptor->size = sizeof(DisconnectCommand);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Command"));

    TypeFactoryRegister::hook("DisconnectCommand", []() -> const TypeDescriptor& { return DisconnectCommandType::s_typeDescriptor; }, []() -> void* { return new DisconnectCommand(); });
}

const TypeDescriptor& PingCommand::get_descriptor() const
{
    return PingCommandType::descriptor();
}

fields_t PingCommand::get_fields() const
{
    return PingCommandType::fields(this);
}

void PingCommand::autoload()
{
    TypeFactory::load<PingCommand>();
}

const TypeDescriptor& PingCommand::descriptor()
{
    return PingCommandType::descriptor();
}

TypeDescriptor PingCommandType::s_typeDescriptor{ PingCommandType::registerTypeDescriptor };

const TypeDescriptor& PingCommandType::descriptor()
{
    return s_typeDescriptor;
}

fields_t PingCommandType::fields(const PingCommand* const)
{
    return fields_t();
}

void PingCommandType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "PingCommand";
    descriptor->size = sizeof(PingCommand);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Command"));

    TypeFactoryRegister::hook("PingCommand", []() -> const TypeDescriptor& { return PingCommandType::s_typeDescriptor; }, []() -> void* { return new PingCommand(); });
}

const TypeDescriptor& UpdateWorldCommand::get_descriptor() const
{
    return UpdateWorldCommandType::descriptor();
}

fields_t UpdateWorldCommand::get_fields() const
{
    return UpdateWorldCommandType::fields(this);
}

void UpdateWorldCommand::autoload()
{
    TypeFactory::load<UpdateWorldCommand>();
}

const TypeDescriptor& UpdateWorldCommand::descriptor()
{
    return UpdateWorldCommandType::descriptor();
}

TypeDescriptor UpdateWorldCommandType::s_typeDescriptor{ UpdateWorldCommandType::registerTypeDescriptor };

const TypeDescriptor& UpdateWorldCommandType::descriptor()
{
    return s_typeDescriptor;
}

fields_t UpdateWorldCommandType::fields(const UpdateWorldCommand* const)
{
    return fields_t();
}

void UpdateWorldCommandType::registerTypeDescriptor(TypeDescriptor* descriptor)
{
    descriptor->name = "UpdateWorldCommand";
    descriptor->size = sizeof(UpdateWorldCommand);
    descriptor->attributes.insert(std::make_pair<std::string, std::string>("Category", "Command"));

    TypeFactoryRegister::hook("UpdateWorldCommand", []() -> const TypeDescriptor& { return UpdateWorldCommandType::s_typeDescriptor; }, []() -> void* { return new UpdateWorldCommand(); });
}

} // namespace command
} // namespace net
