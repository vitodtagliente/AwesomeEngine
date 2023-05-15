/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>

#include <awesome/asset/user_interface_asset.h>
#include <awesome/core/singleton.h>

#include "control.h"

class UIGraph final : public Singleton<UIGraph>
{
public:
	enum class State
	{
		Loading,
		Ready
	};

	Control& root() { return m_root; }
	inline const UserInterfaceAsset& ui() const { return m_ui; }
	inline State state() const { return m_state; }

	void clear();
	void update(double deltaTime);

	bool load(const UserInterfaceAsset& scene);
	bool save(const std::filesystem::path& path);

private:
	Control m_root;
	UserInterfaceAsset m_ui;
	State m_state{ State::Ready };
};