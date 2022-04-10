#include "scene.h"

#include <fstream>

#include <awesome/data/archive.h>
#include <awesome/encoding/json.h>

Scene::Scene()
{
}

Scene::Scene(const Scene& other)
{
}

Scene::~Scene()
{
}

Scene Scene::load(const std::filesystem::path& filename)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	Scene scene;
	// json::value data = json::Deserializer::parse(read(filename));
	// prefab.entity.deserialize(data);
	return scene;
}

void Scene::save(const std::filesystem::path& filename)
{
	Archive ar(filename, Archive::Mode::Write);
	// ar << json::Serializer::to_string(entity.serialize());
}

Scene& Scene::operator=(const Scene& other)
{
	return *this;
}

bool Scene::operator==(const Scene& other) const
{
	return false;
}

bool Scene::operator!=(const Scene& other) const
{
	return false;
}
