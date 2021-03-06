#include <awesome/awesome.h>

using namespace awesome;

class ShinyGalaxy final : public Engine::Module
{
public:

private:

	virtual bool startup_implementation() override;
	virtual void shutdown_implementation() override;
	virtual void update_implementation() override;

	virtual void pre_rendering_implementation() override;
	virtual void render_implementation() override;
	virtual void post_rendering_implementation() override;

	// #todo
	vector3 mousePositionToWorld(const vector2& t_position) const;

	// background color
	Color m_backgroundColor;
	// renderer
	Renderer* m_renderer;
	// time
	Time* m_time;
	// input
	Input* m_input;
	// window
	Window* m_window;

	// sprite material
	// Material* m_spriteMaterial;

};