/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/serialization.h>

class AssetSerializer : public Serializer::IFieldSerializer
{
public:
	virtual bool canSerialize(const FieldDescriptor& field) override;
	virtual json::value serialize(const FieldDescriptor& field) override;
	virtual bool deserialize(FieldDescriptor& field, const json::value& value) override;

	PROTO()
};