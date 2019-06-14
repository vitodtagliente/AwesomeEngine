#pragma once

#include <vector>
#include <awesome/core/singleton.h>

namespace awesome
{
	class EditorElement;

	class Editor : public Singleton<Editor>
	{
	public:

		Editor();
		~Editor();
		
	private:

		// editor elmements
		std::vector<EditorElement*> m_elements;
	};
}
