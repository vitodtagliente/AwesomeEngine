#pragma once

#include <vector>
#include <awesome/core/singleton.h>

namespace awesome
{
	class EditorView;

	class Editor : public Singleton<Editor>
	{
	public:

		Editor();
		~Editor();

		template <typename T = EditorView>
		T * const show()
		{
			T* const view = new T{};
			m_views.push_back(view);
			return view;
		}

		template <typename T = EditorView>
		T * const getView() const
		{
			for (EditorView* const view : m_views)
			{
				if (T * found_view = dynamic_cast<T*>(view))
					return found_view;
			}
			return nullptr;
		}

		void initialize();
		void render();
		
		// if true the editor is visible
		bool enabled;

	private:

		// editor elmements
		std::vector<EditorView*> m_views;
	};
}
