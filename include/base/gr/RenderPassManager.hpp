/**
 * @file RenderPassManager.hpp
 *
 */

#ifndef RENDERPASSMANAGER_HPP_
#define RENDERPASSMANAGER_HPP_

#include "gr/RenderPass.hpp"
#include "gr/BufferManager.hpp"

#include <PrivateHandle.hpp>
#include <NonCopyable.hpp>

#include <list>
#include <queue>

namespace gr {

class RenderPassManager : NonCopyable
{
private:
	typedef std::list<RenderPass>::iterator render_pass_iterator;

public:
	class RenderPassHandle : public PrivateHandle<render_pass_iterator>
	{
		RenderPassHandle() : PrivateHandle<render_pass_iterator>() {}
		RenderPassHandle(const render_pass_iterator& v) : PrivateHandle<render_pass_iterator>(v) {}

		friend class RenderPassManager;
	};

	RenderPassManager();
	RenderPassManager(RenderPassManager&& other);

	RenderPassHandle addRenderPass(RenderPass&& renderPass);
	void removeRenderPass(RenderPassHandle handle);

	void updateRenderPasses();
	void executeRenderPasses();

private:
	std::list<RenderPass> _renderPasses;

#ifdef _DEBUG
	bool _usingPasses;
#endif
};

}


#endif /* RENDERPASSMANAGER_HPP_ */
