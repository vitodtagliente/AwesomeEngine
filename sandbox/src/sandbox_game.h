#include <awesome/awesome.h>

using namespace awesome;

class SandboxGame final : public Module
{
public:

private:

	virtual bool startup_implementation() override;
	virtual void shutdown_implementation() override;
	virtual void update_implementation() override;

	// background color
	Color m_color;
	// triangle color
	Color m_triangleColor;
	// shader program
	ShaderProgram* m_program;
	// texture
	Texture* m_texture;
	// square object
	Renderable* m_sprite;

};