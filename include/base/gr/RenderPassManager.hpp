/**
 * @file RenderPassManager.hpp
 *
 */

#ifndef RENDERPASSMANAGER_HPP_
#define RENDERPASSMANAGER_HPP_

#include "gr/RenderPass.hpp"

#include <text/util.hpp>

#include <PrivateHandle.hpp>
#include <NonCopyable.hpp>

#include <map>

namespace gr {

/**
 * Render pass composition.
 *
 * TODO Missing functionality for ordering render passes.
 */
class RenderPassManager : NonCopyable
{
public:
	typedef text::string_hash render_pass_id;

	RenderPassManager();
	RenderPassManager(RenderPassManager&& other);

	// May not be called while iterating.
	void addRenderPass(render_pass_id id, RenderPass&& renderPass);
	void removeRenderPass(render_pass_id id);
	//

	RenderPass& pass(render_pass_id id);

	void updateRenderPasses();
	void executeRenderPasses();

private:
	std::map<render_pass_id, RenderPass> _renderPasses;

	bool _usingPasses; // Safety check.
};

}


#endif /* RENDERPASSMANAGER_HPP_ */
