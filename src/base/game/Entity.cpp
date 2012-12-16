/**
 * @file Entity.cpp
 *
 */

#include "game/Entity.hpp"
#include <Assert.hpp>

namespace game {

namespace {

const int writeIndex = 0;
const int readIndex = 1;

}

EntityManager::EntityView::EntityView(Components& writeBuffer,
                                      const Components* readBuffer)
		: _readBuffer(readBuffer),
		  _writeBuffer(writeBuffer)
{
}

Component::Writer EntityManager::EntityView::addComponent(component_id compId)
{
	auto it = _writeBuffer.insert(std::pair<
	        component_id, Component>(compId,
	                                 Component())).first;
	return Component::Writer((*it).second);
}

void EntityManager::EntityView::removeComponent(component_id compId)
{
	_writeBuffer.erase(compId);
}

Component::Writer EntityManager::EntityView::findWriter(component_id compId)
{
	return Component::Writer(_writeBuffer.at(compId));
}

const Component::Reader EntityManager::EntityView::findReader(component_id compId) const
{
	ASSERT(_readBuffer != nullptr, "Reader not created yet, flip buffers first.");
	return Component::Reader(_readBuffer->at(compId));
}

concurrency::Mutex& EntityManager::flipMutex() const
{
	return _flipMutex;
}

void EntityManager::flipBuffers()
{
	concurrency::MutexLockGuard lock(_flipMutex);
	_entitiesBuffer[readIndex] = _entitiesBuffer[writeIndex];
}

bool EntityManager::tryFlipBuffers()
{
	ASSERT(false, "Not implemented yet.");

	return true;
}

EntityManager::EntityView EntityManager::findEntity(entity_id entId)
{
	Entities::iterator itRead = _entitiesBuffer[readIndex].find(entId);

	if (itRead == _entitiesBuffer[readIndex].end())
		return EntityView(_entitiesBuffer[writeIndex].at(entId));
	else
		return EntityView(_entitiesBuffer[writeIndex].at(entId),
		                  &itRead->second);
}

EntityManager::EntityView EntityManager::addEntity(entity_id entId)
{
	Entities::iterator itWrite =
		_entitiesBuffer[writeIndex].insert(std::pair<entity_id, Components>(entId, Components())).first;

	return EntityView(itWrite->second);
}

void EntityManager::removeEntity(entity_id entId)
{
	_entitiesBuffer[writeIndex].erase(entId);
}

}
