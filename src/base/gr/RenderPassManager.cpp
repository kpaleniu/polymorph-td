#include "gr/RenderPassManager.hpp"

#include <Scoped.hpp>
#include <Assert.hpp>

namespace gr {

RenderPassManager::RenderPassManager()
:	_renderPasses()
#ifdef _DEBUG
 	, _usingPasses(false)
#endif
{
}

RenderPassManager::RenderPassManager(RenderPassManager&& other)
:	_renderPasses(std::move(other._renderPasses))
#ifdef _DEBUG
	, _usingPasses(false)
#endif
{
#ifdef _DEBUG
	ASSERT(!other._usingPasses, "Trying to move render passes while iterating.");
#endif
}

RenderPassManager::RenderPassHandle RenderPassManager::addRenderPass(RenderPass&& renderPass)
{
#ifdef _DEBUG
	ASSERT(!_usingPasses, "Trying to insert pass while iterating.");
#endif

	return _renderPasses.insert(_renderPasses.end(), std::move(renderPass));
}

void RenderPassManager::removeRenderPass(RenderPassHandle handle)
{
#ifdef _DEBUG
	ASSERT(!_usingPasses, "Trying to remove pass while iterating.");
#endif

	_renderPasses.erase(handle);
}

void RenderPassManager::updateRenderPasses()
{
#ifdef _DEBUG
	Scoped usingScope([this]{_usingPasses = true;},
	                  [this]{_usingPasses = false;});
#endif

	for (auto& pass : _renderPasses)
		pass.updateVertices();
}

void RenderPassManager::executeRenderPasses()
{
#ifdef _DEBUG
	Scoped usingScope([this]{_usingPasses = true;},
	                  [this]{_usingPasses = false;});
#endif

	for (auto& pass : _renderPasses)
		pass.render();
}

}
