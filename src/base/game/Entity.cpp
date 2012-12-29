/**
 * @file Entity.cpp
 *
 */

#include "game/Entity.hpp"

#include <Debug.hpp>
#include <Assert.hpp>

namespace game {

namespace {
const char* TAG = "EntityManager";
}

// EntityReadView

EntityManager::EntityReadView::EntityReadView(const Components& readBuffer)
:	_readBuffer(readBuffer)
{
}

bool EntityManager::EntityReadView::hasComponent(component_id compId) const
{
	return _readBuffer.find(compId) != _readBuffer.end();
}

const Component::Reader EntityManager::EntityReadView::findReader(component_id compId) const
{
	return Component::Reader(_readBuffer.at(compId));
}

// EntityWriteView

EntityManager::EntityWriteView::EntityWriteView(Components& writeBuffer)
:	_writeBuffer(writeBuffer)
{
}

Component::Writer EntityManager::EntityWriteView::findWriter(component_id compId)
{
	return Component::Writer(_writeBuffer.at(compId));
}

Component::Writer EntityManager::EntityWriteView::addComponent(component_id compId)
{
	auto it = _writeBuffer.insert(
				std::pair<component_id, Component>(compId, Component())).first;
	return Component::Writer((*it).second);
}

void EntityManager::EntityWriteView::removeComponent(component_id compId)
{
	_writeBuffer.erase(compId);
}

// EntityView

EntityManager::EntityView::EntityView(const Components& readBuffer, Components& writeBuffer)
:	EntityReadView(readBuffer),
 	EntityWriteView(writeBuffer)
{
}

// EntityManager

concurrency::Mutex& EntityManager::flipMutex() const
{
	return _flipMutex;
}

void EntityManager::flipBuffers()
{
	concurrency::MutexLockGuard lock(_flipMutex);

	_readBuffer = _writeBuffer; // Invalidates iterators?
}

bool EntityManager::tryFlipBuffers()
{
	ASSERT(false, "Not implemented yet.");

	return true;
}

EntityManager::EntityView EntityManager::findEntity(entity_id entId)
{
	return EntityView(_readBuffer.at(entId), _writeBuffer.at(entId));
}

EntityManager::EntityReadView EntityManager::findEntity(entity_id entId) const
{
	return EntityReadView(_readBuffer.at(entId));
}

EntityManager::EntityWriteView EntityManager::addEntity(entity_id entId)
{
	Entities::iterator itWrite =
		_writeBuffer.insert(std::pair<entity_id, Components>(entId, Components())).first;

	return EntityWriteView(itWrite->second);
}

void EntityManager::removeEntity(entity_id entId)
{
	_writeBuffer.erase(entId);
}

}
