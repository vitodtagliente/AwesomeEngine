#include "asset_filesystem.h"

#include <awesome/core/string_util.h>

#include "asset_library.h"

void AssetFilesystem::move(const Asset::Descriptor& descriptor, const std::filesystem::path& path)
{
	static const auto renameAsset = [](const std::filesystem::path& from, const std::filesystem::path& to) -> std::filesystem::path
	{
		std::filesystem::path path = to / from.filename();
		int i = 1;
		while (std::filesystem::exists(path))
		{
			path += (" " + std::to_string(i));
		}
		return path;
	};

	if (!std::filesystem::exists(descriptor.path)
		|| !std::filesystem::is_directory(path))
	{
		return;
	}

	AssetLibrary& library = AssetLibrary::instance();
	std::shared_ptr<Asset> asset = library.find(descriptor.id);
	if (asset)
	{
		const auto& newPath = renameAsset(descriptor.path, path);
		if (newPath == descriptor.path) return;

		std::filesystem::rename(descriptor.path, newPath);
		std::filesystem::rename(descriptor.getDataPath(), renameAsset(descriptor.getDataPath(), path));

		asset->descriptor.path = newPath;
		library.insert(descriptor);
	}
}

bool AssetFilesystem::remove(const Asset::Descriptor& descriptor)
{
	if (!std::filesystem::exists(descriptor.path))
	{
		return false;
	}

	AssetLibrary& library = AssetLibrary::instance();
	std::shared_ptr<Asset> asset = library.find(descriptor.id);
	if (asset)
	{
		library.unload(descriptor.id);
		library.remove(descriptor.id);

		return std::filesystem::remove(descriptor.path)
			&& std::filesystem::remove(descriptor.getDataPath());
	}
	return false;
}

void AssetFilesystem::rename(const Asset::Descriptor& descriptor, const std::string& name)
{
	static const auto renameAsset = [](const std::filesystem::path& filename, const std::string& renaming) -> std::filesystem::path
	{
		std::filesystem::path name = filename.stem();
		while (name.has_extension())
		{
			name = name.stem();
		}

		std::filesystem::path rename = renaming;
		while (rename.has_extension())
		{
			rename = rename.stem();
		}

		return StringUtil::replace(filename.string(), name.string(), rename.string());
	};

	if (!std::filesystem::exists(descriptor.path)
		|| name.empty())
	{
		return;
	}

	AssetLibrary& library = AssetLibrary::instance();
	std::shared_ptr<Asset> asset = library.find(descriptor.id);
	if (asset)
	{
		const auto& newPath = renameAsset(descriptor.path, name);
		if (newPath == descriptor.path) return;

		std::filesystem::rename(descriptor.path, newPath);
		std::filesystem::rename(descriptor.getDataPath(), renameAsset(descriptor.getDataPath(), name));

		asset->descriptor.path = newPath;
		library.insert(asset->descriptor);
	}
}
