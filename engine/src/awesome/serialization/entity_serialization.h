/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/scene/entity.h>

#include "serialization.h"

json::value operator<< (json::value& data, const std::vector<Entity>& value);
json::value operator>> (json::value& data, std::vector<Entity>& value);
json::value operator<< (json::value& data, const std::vector<std::unique_ptr<Entity>>& value);
json::value operator>> (json::value& data, std::vector<std::unique_ptr<Entity>>& value);