/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

#include "control_behaviour_generated.h"

class Control;

CLASS()
class ControlBehaviour : public IType
{
public:
	struct Metrics
	{
		std::size_t count{ 0 };
		std::size_t size{ 0 };
	};

	ControlBehaviour() = default;
	ControlBehaviour(const ControlBehaviour& other);
	virtual ~ControlBehaviour() = default;

	ControlBehaviour& operator= (const ControlBehaviour& other) = delete;
	bool operator== (const ControlBehaviour& other) const;
	bool operator!= (const ControlBehaviour& other) const;

	inline const uuid& getId() const { return m_id; }
	inline Control* const getOwner() const { return m_owner; }

	inline bool isAttached() const { return m_owner != nullptr; }

	void attach(Control* const entity);
	void detach();

	virtual void init() {}
	virtual void uninit() {}
	virtual void update(double /*deltaTime*/) {}

	static const Metrics& metrics() { return s_metrics; }

	PROPERTY() bool enabled{ true };

	GENERATED_BODY()

private:
	PROPERTY() uuid m_id;
	Control* m_owner{ nullptr };

	static inline Metrics s_metrics;
};