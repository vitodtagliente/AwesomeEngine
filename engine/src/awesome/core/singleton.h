/// Copyright (c) Vito Domenico Tagliente
#pragma once

template<typename T>
class Singleton
{
public:
	Singleton() = default;
	virtual ~Singleton() = default;

	// cannot move or copy
	Singleton& operator=(Singleton&&) = delete;
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator= (const Singleton&) = delete;

	// get the singleton instance, thread safe
	static T& instance()
	{
		static T s_instance;
		return s_instance;
	}
};