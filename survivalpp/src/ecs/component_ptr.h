#pragma once

#include "core/uuid.h"

class Component;

template <typename T = Component>
class ComponentPtr
{
public:
	ComponentPtr() = default;
	ComponentPtr(T* const component)
	{
		if (component)
		{
			m_data = component;
			m_id = component->id();
		}
	}
	
	inline operator bool() const
	{
		return m_data != nullptr && m_data->id() == m_id;
	}

	inline ComponentPtr& operator=(T* const component)
	{
		if (component)
		{
			m_data = component;
			m_id = component->id();
		}
		return *this;
	}

	inline bool operator== (const ComponentPtr& other) const { return m_id == other.m_id; }
	inline bool operator!= (const ComponentPtr& other) const { return m_id != other.m_id; }
	
	T* const operator->() const
	{
		return m_data;
	}

	T& operator*() const
	{
		return *m_data;
	}

	T& get() const
	{
		return *m_data;
	}

	void reset()
	{
		m_data = nullptr;
		m_id = uuid::Invalid;
	}

private:
	T* m_data{ nullptr };
	uuid m_id{ uuid::Invalid };
};