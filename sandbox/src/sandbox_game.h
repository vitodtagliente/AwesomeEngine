#include <awesome/awesome.h>

using namespace awesome;

class SandboxGame final : public Module<SandboxGame>
{
public:

private:

	virtual bool startup_implementation() override;
	virtual void shutdown_implementation() override;
	virtual void update_implementation() override;

	Input* m_input{ nullptr };

	// vertex array object
	VertexArray* va;
	// shader program
	ShaderProgram* program;
	// triangle color
	Color triangleColor;
	// texture
	Texture* texture;
	// renderer
	Renderer* renderer;

};