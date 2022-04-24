#include "prefab.h"

#include <fstream>

#include <awesome/data/archive.h>
#include <awesome/encoding/json.h>

Prefab::Prefab()
	: entity()
{
}

Prefab::Prefab(const Entity* const entity)
	: entity()
{
	this->entity.deserialize(entity->serialize());
}

Prefab::Prefab(const Prefab& other)
	: entity()
{
	entity.deserialize(other.entity.serialize());
}

Prefab::~Prefab()
{
}

Prefab Prefab::load(const std::filesystem::path& filename)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	Prefab prefab;
	json::value data = json::Deserializer::parse(read(filename));
	prefab.entity.deserialize(data);
	return prefab;
}

void Prefab::save(const std::filesystem::path& filename)
{
	Archive ar(filename, Archive::Mode::Write);
	ar << json::Serializer::to_string(entity.serialize());
}

Prefab& Prefab::operator=(const Prefab& other)
{
	return *this;
}

bool Prefab::operator==(const Prefab& other) const
{
	return entity.getId() == other.entity.getId();
}

bool Prefab::operator!=(const Prefab& other) const
{
	return entity.getId() != other.entity.getId();
}
