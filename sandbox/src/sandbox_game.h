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
	virtual void uninit() override;
	virtual void end() override;
};