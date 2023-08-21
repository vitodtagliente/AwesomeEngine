#pragma once

#include "ecs/ecs.h"

#include "components/sprite.h"

class SpriteSystem : public System<Sprite>
{
protected:
	virtual void process(double delta_time, Sprite& data);
};