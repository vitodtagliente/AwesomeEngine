/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/encoding/json.h>

json::value operator<< (json::value& data, const IType& value);
json::value operator>> (json::value& data, IType& value);
json::value operator<< (json::value& data, const std::vector<IType>& value);
json::value operator>> (json::value& data, std::vector<IType>& value);
json::value operator<< (json::value& data, const std::vector<std::unique_ptr<IType>>& value);
json::value operator>> (json::value& data, std::vector<std::unique_ptr<IType>>& value);