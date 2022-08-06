/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/serialization.h>

class SpriteAssetSerializer : public Serializer::IFieldSerializer
{
public:
	virtual std::string type() override;
	virtual json::value serialize(const FieldDescriptor& field) override;
	virtual bool deserialize(FieldDescriptor& field, const json::value& value) override;

	PROTO()
};