#include <awesome/object.h>
#include <awesome/component.h>

namespace Awesome
{
	glm::mat4 Object::Transform::get() const
	{
		/* easy in object transform */
		glm::mat4 model(1.0f);
		model = glm::translate(model, position);
		model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, scale);
		return model;
	}

	glm::mat4 Object::Transform::getHierarchy() const
	{
		auto transform_matrix = get();
		auto parent_transform = parent;
		while (parent_transform != nullptr) {
			transform_matrix *= parent->transform.get();
			parent_transform = parent->transform.parent;
		}
		return transform_matrix;
	}

	Object::Object()
	{
		
	}
			
	Object::~Object()
	{

	}

	bool Object::addComponent(Component* new_component)
	{
		if (new_component != nullptr && new_component->owner_object == nullptr)
		{
			new_component->owner_object = this;
			components.push_back(new_component);
			return true;
		}
		return false;
	}

	void Object::addChild(Object* child)
	{
		transform.children.push_back(child);
		child->transform.parent = this;
	}

	bool Object::operator==(const Object& other)
	{
		return id == other.id;
	}

	void Object::setActive(bool active_value)
	{
		/* TODO */
		active = active_value;
	}

	void Object::init()
	{
		for (auto it = components.begin(); it != components.end(); ++it) {
			if (*it != nullptr)
				(*it)->init();
			else components.erase(it);
		}
	}

	void Object::update(float delta_time)
	{
		for (auto it = components.begin(); it != components.end(); ++it) {
			if (*it != nullptr)
				(*it)->update(delta_time);
			else components.erase(it);
		}
	}
}