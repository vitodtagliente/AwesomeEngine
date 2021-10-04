/// Copyright (c) Vito Domenico Tagliente

#pragma once

/// Copyright (c) Vito Domenico Tagliente

#pragma once

class Module
{
public:

	enum class State
	{
		Unknown,
		Error,
		FatalError,
		Started,
		Closed
	};

	Module() = default;
	virtual ~Module() = default;

	virtual State startup() { return m_state = State::Started, m_state; }
	virtual void shutdown() { m_state = State::Closed; }

	virtual void update(const double deltaTime) {}
	virtual void beginRendering() {}
	virtual void render() {}
	virtual void endRendering() {}

	// get the module state
	inline State getState() const { return m_state; }

	virtual bool supportsRenderingPhase() const { return false; }

protected:

	// module state
	State m_state{ State::Unknown };

};