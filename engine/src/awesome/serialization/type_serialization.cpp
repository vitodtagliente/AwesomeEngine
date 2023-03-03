#include "type_serialization.h"

#include "serialization.h"


json::value operator<<(json::value& data, const IType& value)
{
	return json::value();
}

json::value operator>>(json::value& data, IType& value)
{
	return json::value();
}