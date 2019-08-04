#include <awesome/awesome.h>

using namespace awesome;

class ShinyGalaxy final : public Module
{
public:

private:

	virtual bool startup_implementation() override;
	virtual void shutdown_implementation() override;
	virtual void update_implementation() override;

	virtual void pre_rendering_implementation() override;
	virtual void render_implementation() override;
	virtual void post_rendering_implementation() override;

	// background color
	Color m_backgroundColor;
	// renderer
	Renderer* m_renderer;
	// time
	Time* m_time;
	// input
	Input* m_input;

};