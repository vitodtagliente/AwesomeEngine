/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/editor/state.h>
#include <awesome/editor/window.h>

namespace editor
{
	class InspectorWindow : public Window
	{
	public:

		struct Inspector
		{
			Inspector() = default;
			virtual ~Inspector() = default;
			virtual bool canInspect(const State::Selection&) { return false; }
			virtual void update(const State::Selection& , double) {}
			virtual void inspect(const State::Selection&) = 0;
		};

		InspectorWindow();

		std::string getTitle() const override { return "Inspector"; }
		void init() override;
		void update(double deltaTime) override;
		void render() override;

		REFLECT()

	private:
		std::vector<std::unique_ptr<Inspector>> m_inspectors;
	};
}