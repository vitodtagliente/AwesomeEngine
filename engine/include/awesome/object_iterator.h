#pragma once

#include "object.h"

namespace Awesome
{
	class ObjectIterator
	{
	private:
		Object* iterated_object{ nullptr };
		Object* current_object{ nullptr };
		bool can_iterate{ true };

		Object* go_down()
		{
			if (current_object->children().size() > 0)
			{
				return current_object->children()[0];
			}
			return nullptr;
		}

		Object* go_up()
		{
			if (current_object->parent() != iterated_object)
			{
				auto parent = current_object->parent();
				auto brother = find_brother(parent, current_object);
				if (brother != nullptr)
					return brother;
				else
				{
					current_object = current_object->parent();
					return go_up();
				}
			}
			return nullptr;
		}

		Object* find_brother(Object* parent, Object* child)
		{
			if (parent->children().size() > 1)
			{
				bool found_child = false;
				for (int i = 0; i < parent->children().size(); i++)
				{
					if (found_child)
						return parent->children()[i];
					found_child = parent->children()[i] == child;
				}
			}
			return nullptr;
		}

	public:
		ObjectIterator(Object* object)
		{
			iterated_object = object;
			if (iterated_object == nullptr)
				can_iterate = false;
			else
			{
				if (iterated_object->children().size() > 0)
				{
					current_object = current_object->children()[0];
				}
				else can_iterate = false;
			}
		}

		Object& operator*() { return *current_object; }
		Object* operator->() { return current_object; }
		ObjectIterator operator++()
		{
			auto next_object = go_down();
			if (next_object != nullptr)
			{
				current_object = next_object;
			}
			else
			{
				next_object = go_up();
				if (next_object != nullptr)
					current_object = next_object;
				else
				{
					can_iterate = false;
				}
			}
			return *this;
		}

		bool operator==(const ObjectIterator& it){ return current_object == it.current_object; }
		bool operator!=(const ObjectIterator& it) { return current_object != it.current_object; }

		bool has_next() const { return can_iterate; }
	};
}