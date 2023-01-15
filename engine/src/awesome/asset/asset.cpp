#include "asset.h"

bool Asset::operator==(const Asset& other) const
{
	return id == other.id;
}

bool Asset::operator!=(const Asset& other) const
{
	return id != other.id;
}