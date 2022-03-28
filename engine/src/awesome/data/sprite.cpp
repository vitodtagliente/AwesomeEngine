#include "sprite.h"

Sprite::Sprite()
	: image()
	, rect()
{
}

Sprite::Sprite(const ImageAssetPtr& image)
	: image(image)
	, rect()
{
}

Sprite::Sprite(const ImageAssetPtr& image, const graphics::TextureRect& rect)
	: image(image)
	, rect(rect)
{
}

Sprite::Sprite(const Sprite& other)
	: image(other.image)
	, rect(other.rect)
{
}

Sprite::~Sprite()
{
}

Sprite& Sprite::operator=(const Sprite& other)
{
	image = other.image;
	rect = other.rect;
	return *this;
}

bool Sprite::operator==(const Sprite& other) const
{
	return image == other.image && rect == other.rect;
}

bool Sprite::operator!=(const Sprite& other) const
{
	return image != other.image || rect != other.rect;
}
