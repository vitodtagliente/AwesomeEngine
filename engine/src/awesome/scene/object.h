#pragma once

#include <vector>
#include "../data/string_id.h"

namespace awesome
{
	class Component;

	class Object
	{
	public:

		Object();
		virtual ~Object();

		// get the id
		inline unsigned int getId() const { return m_id; }

		// name 
		inline void setName(const StringId& t_name) { m_name = t_name; }
		inline const StringId& getName() const { return m_name; }

		// object transform
		// #todo

		// children management
		inline const std::vector<Object*>& getChildren() const { return m_children; }
		inline unsigned int getChildrenNum() const { return static_cast<unsigned int>(m_children.size()); }
		Object* const getChildById(unsigned int t_id) const;
		Object* const getChildByIndex(unsigned int t_index) const;
		Object* const getChildByName(const StringId& t_name) const;
		Object* const getChildByName(const std::string& t_name) const;
		template <typename T = Object>
		Object* const getChild() const
		{
			for (Object* const child : m_children)
			{
				if (T * const found_child = dynamic_cast<T>(child))
					return found_child;
			}
			return nullptr;
		}
		
		void addChild(Object* const t_child);
		bool removeChild(Object* const t_child);

		// transform utilities
		// #todo

		// component utilities
		inline const std::vector<Component*>& getComponents() const { return m_components; }
		inline unsigned int getComponentsNum() const { return static_cast<unsigned int>(m_components.size()); }
		Component* const getComponentByName(const StringId& t_name) const;
		Component* const getComponentByName(const std::string& t_name) const;
		template <typename T = Component>
		T* const getComponent() const
		{
			for (Component* const component : m_components)
			{
				if (T * const found_component = dynamic_cast<T>(component))
					return found_component;
			}
			return nullptr;
		}
		template <typename T = Component>
		std::vector<T* const> getComponents() const
		{
			std::vector<T* const> found_components;
			for (Component* const component : m_components)
			{
				for (Component* const component : m_components)
				{
					if (T * const found_component = dynamic_cast<T>(component))
						found_components.push_back(found_component);
				}
			}
			return std::move(found_components);
		}

		// object lifetime
		void initialize();

	protected:

		// object lifetime
		virtual void initialize_implementation() {};

	private:

		// object id
		unsigned int m_id;
		// object name
		StringId m_name;
		// transform
		//transform m_transform;
		// children
		std::vector<Object*> m_children;
		// components
		std::vector<Component*> m_components;
	};
}