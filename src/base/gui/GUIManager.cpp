#include "gui/GUIManager.hpp"

#include <text/util.hpp>

#include <Assert.hpp>

namespace gui {

namespace {
// Note, this restricts one GUI render pass per RenderPassManager.
constexpr gr::RenderPassManager::render_pass_id GUI_RENDER_PASS_ID = text::hash("__internal_render_pass_id");
}

GUIManager::GUIManager(sys::UISystem& uiSys, sys::GraphicsSystem& grSys)
:	_uiSys(uiSys),
 	_grSys(grSys)
{
	using namespace gr;

	grSys.actionQueue().pushAction([](sys::GraphicsSystemRunner& runner)
	{
		auto& renderer = runner.renderer();
		auto& passManager = renderer.renderPassManager();
		auto& surface = runner.surface();
		auto surfaceRect = surface.getScreenRect();

		RenderPass::BufferDesc bufferDesc;
		bufferDesc.clearFlags = enum_t(BufferFlag::COLOR);
		bufferDesc.useFlags = enum_t(BufferFlag::COLOR);

		RenderPass::MaterialDesc materialDesc;
		materialDesc.shader = nullptr;
		materialDesc.texture = nullptr;

		real_t aspectRatio = real_t(surfaceRect.getWidth()) / real_t(surfaceRect.getHeight());

		RenderPass::TransformDesc transformDesc =
		{
			Projection::ortho(0, aspectRatio, 0, 1, 1, -1),
			Transform::identity(),
			Transform::identity()
		};

		RenderPass guiPass(renderer.bufferManager(),
		                   VertexFormat::V2,
		                   Primitive::QUADS,
		                   materialDesc,
		                   bufferDesc,
		                   transformDesc);

		passManager.addRenderPass(GUI_RENDER_PASS_ID, std::move(guiPass));
	});
}

GUIManager::~GUIManager()
{
	_grSys.actionQueue().pushAction([](sys::GraphicsSystemRunner& runner)
	{
		auto& passManager = runner.renderer().renderPassManager();

		passManager.removeRenderPass(GUI_RENDER_PASS_ID);
	});
}

void GUIManager::pushPage(Page&& page)
{
	_pages.push(std::move(page));
	setPage(_pages.top());
}

void GUIManager::popPage()
{
	_pages.pop();
	setPage(_pages.top());
}

void GUIManager::setPage(const Page& page)
{
	// TODO Update render pass and event system.
}

}
