/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <string>
#include <vector>

#include <awesome/core/singleton.h>
#include <awesome/scene/component.h>

struct ComponentRecord final
{
	ComponentRecord(const std::string& name, const std::string& category);
	
	Component* const instantiate() const;

	template <typename T = Component>
	T* const instantiate() const
	{
		return reinterpret_cast<T*>(instantiate());
	}

	std::string name;
	std::string category;
};

class ComponentLibrary final : public Singleton<ComponentLibrary>
{
public:
	ComponentLibrary() = default;
	~ComponentLibrary() = default;

	inline const std::vector<ComponentRecord>& records() const { return m_records; }

	const ComponentRecord* const find(const std::string& name) const;
	void push_back(const ComponentRecord& record);

private:
	std::vector<ComponentRecord> m_records;
};