/**
 * @file Entity.hpp
 *
 */

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "game/Component.hpp"
#include "concurrency/Mutex.hpp"
#include "text/util.hpp"

#include <map>
#include <array>

namespace game {

typedef text::string_hash entity_id;
typedef text::string_hash component_id;

typedef std::map<component_id, Component> Components;
typedef std::map<entity_id, Components> Entities;

class EntityManager
{
public:


	class EntityView
	{
	public:
		EntityView(Components& writeBuffer,
		           const Components* readBuffer=nullptr); // At creation, read buffer doesn't exist.

		Component::Writer addComponent(component_id compId);
		void removeComponent(component_id compId);

		Component::Writer findWriter(component_id compId);
		const Component::Reader findReader(component_id compId) const;

	private:
		const Components* _readBuffer;
		Components& _writeBuffer;
	};


	concurrency::Mutex& flipMutex() const;

	void flipBuffers();
	bool tryFlipBuffers();

	EntityView findEntity(entity_id entId);
	EntityView addEntity(entity_id entId);
	void removeEntity(entity_id entId);

private:
	std::array<Entities, 2> _entitiesBuffer;

	mutable concurrency::Mutex _flipMutex;
};

}


#endif /* ENTITY_HPP_ */
