/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <bitset>
#include <cstdint>

// Source: https://gist.github.com/Lee-R/3839813
constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
{
	return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u; // NOLINT (hicpp-signed-bitwise)
}

constexpr std::uint32_t operator "" _hash(char const* s, std::size_t count)
{
	return fnv1a_32(s, count);
}

using EntityStorageId = std::uint32_t;
constexpr EntityStorageId MAX_ENTITIES = 5000;
using ComponentContainerId = std::uint8_t;
constexpr ComponentContainerId MAX_COMPONENTS = 128;
using Signature = std::bitset<MAX_COMPONENTS>;

#define ECS_STORAGE_COMPONENT_DECLARE(CLASS_NAME) \
	virtual Component* attach(Entity* const entity) override; \
	static Component* attach_static(Entity* const, CLASS_NAME&& rval); \
	bool isStorageEnabled() const override { return true; } \
	virtual void detach() override; \
	static void detach_static(Entity* const); \
	virtual std::unique_ptr<Component> persistentCopy(Entity* const) const override; \

#define ECS_STORAGE_COMPONENT_DEFINE(CLASS_NAME) \
	Component* CLASS_NAME::attach(Entity* const entity) \
	{ \
		static_assert(std::is_base_of_v<Component, CLASS_NAME>); \
		Component::attach(entity); \
		return CLASS_NAME::attach_static(entity, std::move(*this)); \
	} \
	Component* CLASS_NAME::attach_static(Entity* const entity, CLASS_NAME&& rval) \
	{ \
		return &EntitiesCoordinator::instance().AddComponent(entity->storageRef, std::move(rval)); \
	} \
	void CLASS_NAME::detach() \
	{ \
		static_assert(std::is_base_of_v<Component, CLASS_NAME>); \
		Entity* const entity = getOwner(); \
		Component::detach(); \
		CLASS_NAME::detach_static(entity); \
	} \
	void CLASS_NAME::detach_static(Entity* const entity) \
	{ \
		EntitiesCoordinator::instance().RemoveComponent<CLASS_NAME>(entity->storageRef); \
	} \
	std::unique_ptr<Component> CLASS_NAME::persistentCopy(Entity* const entity) const \
	{ \
		auto tmp = std::make_unique<CLASS_NAME>(*this); \
		tmp->m_owner = entity; \
		return tmp; \
	}