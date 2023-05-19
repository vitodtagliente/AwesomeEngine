/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/engine/engine_module.h>

class AudioModule : public EngineModule
{
public:
	AudioModule();

	virtual bool startup() override;
	virtual void shutdown() override;

	void* const context() const;
	template <typename T>
	T* const context() const
	{
		return static_cast<T*>(context());
	}

	static AudioModule* const instance() { return s_instance; }

private:
	static inline AudioModule* s_instance{ nullptr };
};