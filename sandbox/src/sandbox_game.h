#include <awesome/awesome.h>

using namespace awesome;

class SandboxGame final : public Module<SandboxGame>
{
public:

private:

	virtual bool startup_imp() override;
	virtual void shutdown_imp() override;
	virtual void update_imp() override;

	Input* m_input{ nullptr };

/*
	SandboxGame();
	virtual ~SandboxGame() override;

protected:

	virtual void init() override;
	virtual void update(const double delta_time) override;
	virtual void draw() override;
	virtual void uninit() override;
	virtual void end() override;

private:

	// vertex array object
	VertexArray* va;
	// shader program
	ShaderProgram* program;
	// triangle color
	Color triangleColor;
	// texture
	Texture* texture;
	*/
};