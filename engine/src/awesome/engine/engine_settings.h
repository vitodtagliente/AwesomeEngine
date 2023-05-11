// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <filesystem>
#include <memory>

#include <awesome/asset/scene_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/graphics/color.h>

#include "engine_settings_generated.h"

ENUM()
enum class EngineMode : int
{
    Editor = 0,
    Server = 1,
    Standalone = 2,
};

ENUM()
enum class FpsMode : int
{
    Fps30 = 30,
    Fps60 = 60,
    Fps90 = 90,
    Unlimited,
};

CLASS()
struct RendererSettings : public IType
{
    PROPERTY() bool renderCollisions{ true };
    PROPERTY() graphics::Color collisionWireColor{ graphics::Color::Green };
    PROPERTY() bool renderQuadtree{ true };
    PROPERTY() graphics::Color quadtreeWireColor{ graphics::Color::Black };

    GENERATED_BODY()
};

CLASS()
struct SceneSettings : public IType
{
    PROPERTY() SceneAsset editor;
    PROPERTY() SceneAsset server;
    PROPERTY() SceneAsset standalone;

    GENERATED_BODY()
};

CLASS()
struct EngineSettings : public IType
{
    void save() const;
    bool load(const std::filesystem::path& _path);

    PROPERTY() FpsMode fps { FpsMode::Fps60 };
    PROPERTY() EngineMode mode { EngineMode::Editor };

    PROPERTY() RendererSettings renderer;
    PROPERTY() SceneSettings scene;

    std::filesystem::path path;

    static constexpr char* Filename{ "settings.json" };

    GENERATED_BODY()
};
