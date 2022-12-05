#include "particles2d_component.h"

#include <awesome/editor/layout.h>
#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>

/*
math::vec3 position;
math::vec3 direction;
float duration;
int initialParticles;
int maxParticles;
float spawnTime;
std::pair<int, int> spawnAmountRange;
std::pair<Color, Color> particleColorRange;
std::pair<float, float> particleLifetimeRange;
std::pair<float, float> particleSizeRange;
bool particleResizeWithTime;
std::pair<float, float> particleResizeRange;
std::pair<float, float> particleSpeedRange;
TexturePtr particleTexture;
TextureRect particleTextureRect;
PolygonType particlePolygonType;
PolygonStyle particlePolygonStyle;
*/

void Particles2dComponent::init()
{
	if (autoplay)
	{
		m_system.play();
	}
}

void Particles2dComponent::render(graphics::Renderer2D* const renderer)
{
	m_system.render(*renderer);
}

void Particles2dComponent::update(const double deltaTime)
{
	m_system.position = getOwner()->transform.position;
	m_system.update(static_cast<float>(deltaTime));
	if (loop)
	{
		m_system.play();
	}
}

json::value Particles2dComponent::serialize() const
{
	Serializer serializer;
	json::value data = Component::serialize();
	data["autoplay"] = autoplay;
	data["loop"] = loop;
	data["direction"] = serializer.serialize(m_system.direction);
	data["duration"] = m_system.duration;
	data["initialParticles"] = m_system.initialParticles;
	data["maxParticles"] = m_system.maxParticles;
	data["spawnTime"] = m_system.spawnTime;
	data["spawnAmountRange-0"] = m_system.spawnAmountRange.first;
	data["spawnAmountRange-1"] = m_system.spawnAmountRange.second;
	data["particleColorRange-0"] = serializer.serialize(m_system.particleColorRange.first);
	data["particleColorRange-1"] = serializer.serialize(m_system.particleColorRange.second);
	data["particleLifetimeRange-0"] = m_system.particleLifetimeRange.first;
	data["particleLifetimeRange-1"] = m_system.particleLifetimeRange.second;
	data["particleSizeRange-0"] = m_system.particleSizeRange.first;
	data["particleSizeRange-1"] = m_system.particleSizeRange.second;
	data["particleResizeWithTime"] = m_system.particleResizeWithTime;
	data["particleResizeRange-0"] = m_system.particleResizeRange.first;
	data["particleResizeRange-1"] = m_system.particleResizeRange.second;
	data["particleSpeedRange-0"] = m_system.particleSpeedRange.first;
	data["particleSpeedRange-1"] = m_system.particleSpeedRange.second;
	// TexturePtr particleTexture;
	// TextureRect particleTextureRect;
	// PolygonType particlePolygonType;
	// PolygonStyle particlePolygonStyle;
	return data;
}

void Particles2dComponent::deserialize(const json::value& value)
{
	Deserializer deserializer;
	Component::deserialize(value);

	autoplay = value.safeAt("autoplay").as_bool(false);
	loop = value.safeAt("loop").as_bool(false);
	deserializer.deserialize(value["direction"], m_system.direction);
	m_system.duration = value.safeAt("duration").as_number(0.f).as_float();
	m_system.initialParticles = value.safeAt("initialParticles").as_number(0).as_int();
	m_system.maxParticles = value.safeAt("maxParticles").as_number(0).as_int();
	m_system.spawnTime = value.safeAt("spawnTime").as_number(0.f).as_float();
	m_system.spawnAmountRange.first = value.safeAt("spawnAmountRange-0").as_number(0).as_int();
	m_system.spawnAmountRange.second = value.safeAt("spawnAmountRange-1").as_number(0).as_int();
	deserializer.deserialize(value.safeAt("particleColorRange-0"), m_system.particleColorRange.first);
	deserializer.deserialize(value.safeAt("particleColorRange-1"), m_system.particleColorRange.second);
	m_system.particleLifetimeRange.first = value.safeAt("particleLifetimeRange-0").as_number(0.f).as_float();
	m_system.particleLifetimeRange.second = value.safeAt("particleLifetimeRange-1").as_number(0.f).as_float();
	m_system.particleSizeRange.first = value.safeAt("particleSizeRange-0").as_number(0.f).as_float();
	m_system.particleSizeRange.second = value.safeAt("particleSizeRange-1").as_number(0.f).as_float();
	m_system.particleResizeWithTime = value.safeAt("particleResizeWithTime").as_bool(false);
	m_system.particleResizeRange.first = value.safeAt("particleResizeRange-0").as_number(0.f).as_float();
	m_system.particleResizeRange.second = value.safeAt("particleResizeRange-1").as_number(0.f).as_float();
	m_system.particleSpeedRange.first = value.safeAt("particleSpeedRange-0").as_number(0.f).as_float();
	m_system.particleSpeedRange.second = value.safeAt("particleSpeedRange-1").as_number(0.f).as_float();
	// TexturePtr particleTexture;
	// TextureRect particleTextureRect;
	// PolygonType particlePolygonType;
	// PolygonStyle particlePolygonStyle;
	// TEMP
	m_system.particlePolygonType = graphics::PolygonType::circle;
	m_system.particlePolygonStyle = graphics::PolygonStyle::fill;
}

void Particles2dComponent::inspect()
{
	Component::inspect();

	Layout::input("Autoplay", autoplay);
	Layout::input("Loop", loop);
	Layout::input("Direction", m_system.direction);
	Layout::input("Duration", m_system.duration);
	Layout::input("Initial Particles", m_system.initialParticles);
	Layout::input("Max Particles", m_system.maxParticles);
	Layout::input("SpawnTime", m_system.spawnTime);
	Layout::input("Spawn Amount", m_system.spawnAmountRange);
	Layout::input("Particle Color", m_system.particleColorRange);
	Layout::input("Particle Lifetime", m_system.particleLifetimeRange);
	Layout::input("Particle Size", m_system.particleSizeRange);
	Layout::input("Particle Resize With Time", m_system.particleResizeWithTime);
	Layout::input("Particle Resize", m_system.particleResizeRange);
	Layout::input("Particle Speed", m_system.particleSpeedRange);
	// TexturePtr particleTexture;
	// TextureRect particleTextureRect;
	// PolygonType particlePolygonType;
	// PolygonStyle particlePolygonStyle;
}

void Particles2dComponent::play()
{
	m_system.play();
}

void Particles2dComponent::pause()
{
	m_system.pause();
}

void Particles2dComponent::resume()
{
	m_system.resume();
}

void Particles2dComponent::stop()
{
	m_system.stop();
}

bool Particles2dComponent::isPlaying() const
{
	return m_system.isPlaying();
}