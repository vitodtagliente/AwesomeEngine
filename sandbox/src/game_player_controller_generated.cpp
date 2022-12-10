// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#include "game_player_controller.h"

const meta_t& GamePlayerController::getTypeMeta() const { return GamePlayerControllerType::type().meta; }
const std::string& GamePlayerController::getTypeName() const { return GamePlayerControllerType::type().name; }
const properties_t GamePlayerController::getTypeProperties() const {
    properties_t properties = PlayerController::getTypeProperties();
    return properties;
}
std::size_t GamePlayerController::getTypeSize() const { return GamePlayerControllerType::type().size; }

const TypeDefinition& GamePlayerControllerType::type()
{
    static const TypeDefinition s_typeDefinition([]() -> Type* { return new GamePlayerController(); }, "GamePlayerController", {
        std::make_pair("Category", "PlayerController"),
    }, sizeof(GamePlayerController));
    return s_typeDefinition;
}
