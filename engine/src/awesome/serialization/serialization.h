/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>

#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

json::value operator<< (json::value& data, const std::string& value);
json::value operator>> (json::value& data, std::string& value);
json::value operator<< (json::value& data, const std::filesystem::path& value);
json::value operator>> (json::value& data, std::filesystem::path& value);
json::value operator<< (json::value& data, const uuid& value);
json::value operator>> (json::value& data, uuid& value);
json::value operator<< (json::value& data, const math::vec2& value);
json::value operator>> (json::value& data, math::vec2& value);
json::value operator<< (json::value& data, const math::vec3& value);
json::value operator>> (json::value& data, math::vec3& value);
json::value operator<< (json::value& data, const math::vec4& value);
json::value operator>> (json::value& data, math::vec4& value);
json::value operator<< (json::value& data, const math::transform& value);
json::value operator>> (json::value& data, math::transform& value);