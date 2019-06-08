#include <awesome/awesome.h>

using namespace awesome;

class SandboxGame final : public Module
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
	Color m_color;
	// triangle color
	Color m_triangleColor;
	// shader program
	ShaderProgram* m_program;
	// texture
	Texture* m_texture;
	// renderer
	Renderer* m_renderer;
	// sprite material
	Material* m_spriteMaterial;
	// projection matrix
	mat4 m_projection;
	// view matrix : camera transform
	mat4 m_view;

};