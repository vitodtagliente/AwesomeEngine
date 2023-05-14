/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/math/vector2.h>

#include "control_generated.h"

CLASS()
class Control : public IType
{
public:
	Control() = default;
	Control(const uuid& id);
	Control(const Control& other);
	virtual ~Control() = default;

	Control& operator= (const Control& other);
	bool operator== (const Control& other) const;
	bool operator!= (const Control& other) const;

	inline const std::vector<std::unique_ptr<Control>>& children() const { return m_children; }
	inline const uuid& id() const { return m_id; }
	inline Control* const parent() const { return m_parent; }
	inline bool hasChildren() const { return !m_children.empty(); }
	inline bool hasParent() const { return m_parent != nullptr; }

	void queue_destroy();
	void update(double deltaTime);

	std::vector<Control*> findChildrenByTag(const std::string& tag) const;
	Control* const findChildById(const uuid& id, bool recursive = true) const;
	Control* const findChildByName(const std::string& name) const;
	Control* const findChildByTag(const std::string& tag) const;

	Control* const addChild();
	Control* const addChild(std::unique_ptr<Control> child);
	bool removeChild(Control* const Control);
	bool removeChild(const uuid& id);
	void removeChildren();

	PROPERTY() std::string name;
	PROPERTY() std::string tag;
	PROPERTY() math::vec2 localPosition;

	GENERATED_BODY()

private:
	PROPERTY() std::vector<std::unique_ptr<Control>> m_children;
	uuid m_id;
	Control* m_parent{ nullptr };
};