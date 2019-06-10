#pragma once

#include <vector>
#include <awesome/data/string_id.h>
#include <awesome/math/transform.h>

namespace awesome
{
	class Component;

	class Object
	{
	public:

		Object();
		virtual ~Object();

		template <typename T = Object>
		static T * const create()
		{
			T* const created_object = new T{};
			created_object->m_id = StringId::unique();
			return created_object;
		}

		// get the id
		inline const StringId& getId() const { return m_id; }
		
		// children management
		inline const std::vector<Object*>& getChildren() const { return m_children; }
		inline unsigned int getChildrenNum() const { return static_cast<unsigned int>(m_children.size()); }
		Object* const getChildById(const StringId& t_id) const;
		Object* const getChildByIndex(unsigned int t_index) const;
		Object* const getChildByName(const StringId& t_name) const;
		Object* const getChildByName(const std::string& t_name) const;
		template <typename T = Object>
		Object* const getChild() const
		{
			for (Object* const child : m_children)
			{
				if (T * const found_child = static_cast<T>(child))
					return found_child;
			}
			return nullptr;
		}
		// add and remove childrend objects
		void addChild(Object* const t_child);
		bool removeChild(Object* const t_child);

		// return the parent object
		inline Object* const getParent() const { return m_parent; }
		// check if this object is a leaf in scene tree
		inline bool isLeaf() const { return m_children.size() == 0; }
		// check if this object is root in scene tree
		inline bool isRoot() const { return m_parent == nullptr; }

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
				if (T * const found_component = static_cast<T>(component))
					return found_component;
			}
			return nullptr;
		}
		template <typename T = Component>
		std::vector<T*> getComponents() const
		{
			std::vector<T*> found_components;
			for (Component* const component : m_components)
			{
				if (T * const found_component = static_cast<T*>(component))
					found_components.push_back(found_component);
			}
			return std::move(found_components);
		}
		template <typename T = Component>
		T * const addComponent()
		{
			T * const component = Component::create<T>(this);
			m_components.push_back(component);
			component->init();
			return component;
		}
		bool removeComponent(Component* const t_component);

		// object lifetime
		void initialize();
		// object update 
		void update(const double t_deltaTime);
		
		// object name
		StringId name;
		// transform
		transform transform;
		// if true, this object cannot be moved
		bool isStatic;

	protected:

		// object lifetime
		virtual void initialize_implementation() {};
		virtual void update_implementation(const double t_deltaTime){}

	private:

		// object id
		StringId m_id;
		// children
		std::vector<Object*> m_children;
		// parent object
		Object* m_parent;
		// components
		std::vector<Component*> m_components;
	};
}