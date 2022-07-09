/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "camera.h"

namespace component
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera();
		virtual ~OrthographicCamera() = default;

		void update(double deltaTime) override;

		virtual json::value serialize() const override;
		virtual void deserialize(const json::value& value) override;
		virtual void inspect() override;

		float nearPlane{ -30.f };
		float farPlane{ 1000.f };
		bool pixelPerfect{ true };
		int pixelsPerUnit{ 32 };

		REFLECT()
	};
}