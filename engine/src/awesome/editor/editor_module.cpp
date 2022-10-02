#include "editor_module.h"

#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD 
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <awesome/application/canvas.h>
#include <awesome/application/input.h>
#include <awesome/editor/color_scheme.h>
#include <awesome/editor/dialog.h>
#include <awesome/editor/layout.h>

#include <IconsFontAwesome5.h>

namespace editor
{
	void Module::startup()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(Canvas::instance().getHandler()), true);
		ImGui_ImplOpenGL3_Init("#version 330 core");

		// icons setup
		{
			io.Fonts->AddFontDefault();

			// merge in icons from Font Awesome
			static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
			ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
			io.Fonts->AddFontFromFileTTF((std::string("../fonts/") + FONT_ICON_FILE_NAME_FAS).c_str(), 12.0f, &icons_config, icons_ranges);
			// use FONT_ICON_FILE_NAME_FAR if you want regular instead of solid
		}

		ColorScheme scheme;
		scheme.apply();

		m_menu.init();

		registerWindows();
		for (const auto& window : m_windows)
		{
			window->init();
		}
	}

	void Module::shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Module::preRendering()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Module::render(graphics::Renderer2D* const)
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
		m_menu.render();
		if (State::instance().showWindows)
		{
			for (const auto& window : m_windows)
			{
				Layout::begin(window->getTitle());
				window->setFocus(Layout::isWindowFocused());
				window->render();
				Layout::end();
			}
		}

		Dialog::instance().render();
	}

	void Module::postRendering()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Module::update(const double deltaTime)
	{
		Input::instance().preventMouseEvents = ImGui::GetIO().WantCaptureMouse;

		if (State::instance().showWindows)
		{
			for (const auto& window : m_windows)
			{
				window->update(deltaTime);
			}
		}
	}

	void Module::registerWindows()
	{
		static std::vector<std::string> types = TypeFactory::list("Category", "Window");
		for (const std::string& type : types)
		{
			Window* const window = TypeFactory::instantiate<Window>(type);
			if (window)
			{
				m_windows.push_back(std::unique_ptr<Window>(window));
			}
		}
	}
}