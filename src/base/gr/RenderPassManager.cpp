#include "gr/RenderPassManager.hpp"

#include <Scoped.hpp>
#include <Assert.hpp>

namespace gr {

RenderPassManager::RenderPassManager()
:	_renderPasses(),
 	_usingPasses(false)
{
}

RenderPassManager::RenderPassManager(RenderPassManager&& other)
:	_renderPasses(std::move(other._renderPasses)),
	_usingPasses(false)
{
	ASSERT(!other._usingPasses, "Trying to move render passes while iterating.");
}

void RenderPassManager::addRenderPass(render_pass_id id, RenderPass&& renderPass)
{
	ASSERT(!_usingPasses, "Trying to insert pass while iterating.");

	VERIFY(_renderPasses.insert(std::make_pair(id, std::move(renderPass))).second);
}

void RenderPassManager::removeRenderPass(render_pass_id id)
{
	ASSERT(!_usingPasses, "Trying to remove pass while iterating.");

	VERIFY(_renderPasses.erase(id));
}

void RenderPassManager::updateRenderPasses()
{
	Scoped usingScope([this]{_usingPasses = true;},
	                  [this]{_usingPasses = false;});

	for (auto& pass : _renderPasses)
		pass.second.updateVertices();
}

void RenderPassManager::executeRenderPasses()
{
	Scoped usingScope([this]{_usingPasses = true;},
	                  [this]{_usingPasses = false;});

	for (auto& pass : _renderPasses)
		pass.second.render();
}

}
