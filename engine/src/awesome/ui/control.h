/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/math/vector2.h>

#include "control_behaviour.h"

#include "control_generated.h"

CLASS()
class Control : public IType
{
public:
	enum class State
	{
		PendingSpawn,
		Alive,
		PendingDestroy
	};

	Control() = default;
	Control(const uuid& id);
	Control(const Control& other);
	virtual ~Control() = default;

	Control& operator= (const Control& other);
	bool operator== (const Control& other) const;
	bool operator!= (const Control& other) const;

	inline const std::vector<std::unique_ptr<Control>>& children() const { return m_children; }
	inline const std::vector<std::unique_ptr<ControlBehaviour>>& behaviours() const { return m_behaviours; }
	inline const uuid& id() const { return m_id; }
	inline Control* const parent() const { return m_parent; }
	inline State state() const { return m_state; }
	inline bool hasChildren() const { return !m_children.empty(); }
	inline bool hasParent() const { return m_parent != nullptr; }

	std::size_t countChildren() const;
	void moveChild(Control* const parent, const uuid& childId);

	void queue_destroy();
	void update(double deltaTime);

	std::vector<Control*> findChildrenByTag(const std::string& tag) const;
	Control* const findChildById(const uuid& id, bool recursive = true) const;
	Control* const findChildByName(const std::string& name) const;
	Control* const findChildByTag(const std::string& tag) const;

	Control* const addChild();
	Control* const addChild(std::unique_ptr<Control> child);
	bool removeChild(Control* const entity);
	bool removeChild(const uuid& id);
	void removeChildren();

	template <typename T = ControlBehaviour>
	std::vector<T*> findBehaviours() const
	{
		std::vector<T*> found_behaviours;
		for (const auto& behaviour : m_behaviours)
		{
			if (T* const found_behaviour = dynamic_cast<T*>(behaviour.get()))
			{
				found_behaviours.push_back(found_behaviour);
			}
		}
		return found_behaviours;
	}

	template <typename T = ControlBehaviour>
	T* const findBehaviour() const
	{
		for (const auto& behaviour : m_behaviours)
		{
			if (T* const found_behaviour = dynamic_cast<T*>(behaviour.get()))
			{
				return found_behaviour;
			}
		}
		return nullptr;
	}

	template <typename T = ControlBehaviour>
	T* const findBehaviourInChildren() const
	{
		for (const auto& behaviour : m_behaviours)
		{
			if (T* const found_behaviour = dynamic_cast<T*>(behaviour.get()))
			{
				return found_behaviour;
			}
		}

		for (const auto& child : m_children)
		{
			if (T* const found_behaviour = child->findBehaviourInChildren<T>())
			{
				return found_behaviour;
			}
		}
		return nullptr;
	}

	template <typename T = ControlBehaviour>
	std::vector<T*> findBehavioursInChildren() const
	{
		std::vector<T*> result;
		findBehavioursInChildren(result);
		return result;
	}

	template <typename T = ControlBehaviour>
	T* const addBehaviour()
	{
		T* const behaviour = new T();
		m_behaviours.push_back(std::unique_ptr<ControlBehaviour>(behaviour));
		if (m_state == State::Alive)
		{
			behaviour->attach(this);
			behaviour->init();
		}
		return behaviour;
	}

	ControlBehaviour* const addBehaviour(std::unique_ptr<ControlBehaviour> behaviour)
	{
		if (behaviour == nullptr) return nullptr;

		if (m_state == State::Alive)
		{
			behaviour->attach(this);
			behaviour->init();
		}
		m_behaviours.push_back(std::move(behaviour));
		return m_behaviours.back().get();
	}

	void removeBehaviour(ControlBehaviour* const behaviour);
	void removeBehaviour(const uuid& id);

	PROPERTY() bool isFocusable{ true };
	PROPERTY() bool isInteractable{ true };
	PROPERTY() std::string name;
	PROPERTY() math::vec2 position;
	PROPERTY() bool replicate{ false };
	PROPERTY() std::string tag;

	GENERATED_BODY()

private:
	template <typename T = ControlBehaviour>
	void findBehavioursInChildren(std::vector<T*>& found_behaviours) const
	{
		for (const auto& behaviour : m_behaviours)
		{
			if (T* const found_behaviour = dynamic_cast<T*>(behaviour.get()))
			{
				found_behaviours.push_back(found_behaviour);
				break;
			}
		}

		for (const auto& child : m_children)
		{
			child->findBehavioursInChildren(found_behaviours);
		}
	}

	void prepareToDestroy();
	void prepareToSpawn();

	PROPERTY() std::vector<std::unique_ptr<Control>> m_children;
	PROPERTY() std::vector<std::unique_ptr<ControlBehaviour>> m_behaviours;
	uuid m_id;
	Control* m_parent{ nullptr };
	State m_state{ State::PendingSpawn };
};