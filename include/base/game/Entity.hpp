/**
 * @file Entity.hpp
 *
 */

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "game/Component.hpp"
#include <concurrency/Mutex.hpp>
#include <text/util.hpp>

#include <map>
#include <array>

namespace game {

typedef text::string_hash entity_id;
typedef text::string_hash component_id;

typedef std::map<component_id, Component> Components;
typedef std::map<entity_id, Components> Entities;

/**
 * Game entity encapsulation.
 */
class EntityManager
{
public:

	/**
	 * Read access to entity.
	 *
	 * It is only possible to access the read view after the
	 * first buffer flip after the entity's construction.
	 */
	class EntityReadView
	{
	public:
		EntityReadView(const Components& readBuffer);

		bool hasComponent(component_id compId) const;
		const Component::Reader findReader(component_id compId) const;

	private:
		const Components& _readBuffer;
	};

	/**
	 * Write access to entity.
	 *
	 * This view should be used to construct the entity.
	 */
	class EntityWriteView
	{
	public:
		EntityWriteView(Components& writeBuffer);

		Component::Writer findWriter(component_id compId);
		void removeComponent(component_id compId);
		Component::Writer addComponent(component_id compId);

	private:
		Components& _writeBuffer;
	};

	/**
	 * Read / write access to entity.
	 */
	class EntityView : public EntityReadView, public EntityWriteView
	{
	public:
		EntityView(const Components& readBuffer, Components& writeBuffer);
	};


public:
	/**
	 * Buffer flip mutex.
	 */
	concurrency::Mutex& flipMutex() const;

	/**
	 * Flips the buffers.
	 */
	///@{
	void flipBuffers();
	bool tryFlipBuffers(); //< @return	True if flipping occurred, else false.
	///@}

	/**
	 * Entity queries.
	 */
	///@{
	EntityReadView findEntity(entity_id entId) const;
	EntityView findEntity(entity_id entId);
	///@}

	/**
	 * Entity lifetime handling.
	 */
	///@{
	EntityWriteView addEntity(entity_id entId);
	void removeEntity(entity_id entId);
	///@}

private:
	Entities _readBuffer;
	Entities _writeBuffer;

	mutable concurrency::Mutex _flipMutex;
};

}


#endif /* ENTITY_HPP_ */
