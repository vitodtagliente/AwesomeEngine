#include <awesome/core/game.h>

class SandboxGame : public awesome::Game
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