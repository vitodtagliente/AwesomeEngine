#include <awesome/awesome.h>

using namespace awesome;

class SandboxGame : public Game
{
public:

	SandboxGame();
	virtual ~SandboxGame() override;

protected:

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void uninit() override;
	virtual void end() override;

private:

	// vertex array object
	VertexArray* va;
	// shader program
	ShaderProgram* program;
};