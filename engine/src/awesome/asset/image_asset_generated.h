// Copyright (c) Vito Domenico Tagliente
// automatically generated by the compiler, do not modify
#pragma once

#include <vdtreflect/runtime.h>

template <>
struct reflect::Type<struct ImageAsset> : reflect::RegisteredInTypeFactory<struct ImageAsset>
{
    static IType* const instantiate();
    static const reflect::meta_t& meta();
    static const char* const name();
    static const reflect::properties_t& properties();
    static std::size_t size();

    static void from_string(const std::string& str, ImageAsset& type);
    static std::string to_string(const ImageAsset& type);
    static void from_json(const std::string& json, ImageAsset& type);
    static std::string to_json(const ImageAsset& type, const std::string& offset = "");

    static bool registered() { return type_registered; };
};

template <>
struct reflect::Type<struct ImageAssetLoader> : reflect::RegisteredInTypeFactory<struct ImageAssetLoader>
{
    static IType* const instantiate();
    static const reflect::meta_t& meta();
    static const char* const name();
    static const reflect::properties_t& properties();
    static std::size_t size();

    static void from_string(const std::string& str, ImageAssetLoader& type);
    static std::string to_string(const ImageAssetLoader& type);
    static void from_json(const std::string& json, ImageAssetLoader& type);
    static std::string to_json(const ImageAssetLoader& type, const std::string& offset = "");

    static bool registered() { return type_registered; };
};