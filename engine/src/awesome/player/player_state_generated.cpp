// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "player_state.h"

const meta_t& PlayerState::getTypeMeta() const { return PlayerStateType::type().meta; }
const std::string& PlayerState::getTypeName() const { return PlayerStateType::type().name; }
const properties_t PlayerState::getTypeProperties() const {
    member_address_t origin = reinterpret_cast<member_address_t>(this);
    properties_t properties;
    properties.insert(std::make_pair<std::string, Property>("gamertag", Property("gamertag", Property::TypeDescriptor("std::string", Property::Type::T_container_string, Property::DecoratorType::D_normalized, {}), sizeof(std::string), origin + offsetof(PlayerState, gamertag), {
    })));
    return properties;
}
std::size_t PlayerState::getTypeSize() const { return PlayerStateType::type().size; }

const TypeDefinition& PlayerStateType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new PlayerState(); }, "PlayerState", {
        std::make_pair("Category", "PlayerState"),
    }, sizeof(PlayerState));
    return s_typeDefinition;
}
