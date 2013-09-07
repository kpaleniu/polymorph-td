#include "pm_td/MainMenuState.hpp"

#include "pm_td/GameState.hpp"
#include "pm_td/GameRunner.hpp"
#include "pm_td/PlayState.hpp"

#include <gr/Mesh.hpp>
#include <text/util.hpp>

#include <memory>

namespace {

gr::Mesh createRect(gr::real_t left, 
					gr::real_t bottom, 
					gr::real_t width, 
					gr::real_t height,
					gr::TextureManager::TextureHandle texture)
{
	gr::VertexList vl
	(
		gr::VertexFormat::V2, 
		std::vector<gr::real_t>
		{
			left,         bottom,
			left + width, bottom,
			left + width, bottom + height,
			left,         bottom + height
		}
	);

	gr::Mesh rMesh(std::move(vl), gr::Primitive::QUADS);

	rMesh.addSubMesh(texture, std::vector<gr::index_t>{0, 1, 2, 3});

	return rMesh;
}

const text::string_hash RECT_MESH_HASH = text::hash("RECT_MESH_HASH");
const gr::Scene<gr::Transform2>::model_id PLAY_MODEL_ID = text::hash("PLAY_MODEL_ID");
const event_action_id UI_CLICK_ID = text::hash("UI_CLICK_ID");

}


namespace pm_td {

void MainMenuState::enterState(GameRunner& runner)
{
	runner.graphicsSystem().actionQueue().pushAction
	(
		[&runner](polymorph::sys::GraphicsSystemRunner& grRunner) mutable
		{
			gr::Mesh rect = createRect(-0.5f, -0.5f, 1.0f, 1.0f,
									   gr::TextureManager::getNullTexture());

			auto meshHandle = grRunner.meshManager().addMesh(RECT_MESH_HASH, 
															 std::move(rect));

			gr::Model<gr::Transform2> playButtonModel(
					std::vector<gr::Model<gr::Transform2>::ModelMesh>
					{ { gr::Transform2::IDENTITY, meshHandle } });

			{
				auto sceneMutator = runner.graphicsSystem().sceneMutator();
				sceneMutator.scene.addModel(PLAY_MODEL_ID, 
											std::move(playButtonModel));
			}

			runner.uiSystem().addEventAction<polymorph::sys::event::PointerDown>
			(
				UI_CLICK_ID,
				[&](const polymorph::sys::event::PointerDown& arg)
				{
					auto pointPos = arg.pointerPos;

					runner.graphicsSystem().actionQueue().pushAction
					(
						[&runner, pointPos](polymorph::sys::GraphicsSystemRunner& grRunner)
						{
							auto clipPointPos = grRunner.surface().pick(pointPos, 1.0f);
							auto& model = grRunner.scene().model(PLAY_MODEL_ID);

							const auto& v = clipPointPos.operator const gr::Vector3_r &();

							if (model.insideBoundBox(gr::Vector2_r{ v[0], v[1] }))
							{
								runner.system().actionQueue().pushAction
								(
									[](GameRunner& gameRunner)
									{
										gameRunner.setState(
											std::shared_ptr<GameState>(new PlayState()));
									}
								);
							}
						}
					);
				}
			);
		}
	);


}

void MainMenuState::exitState(GameRunner& runner)
{
	{
		auto sceneMutator = runner.graphicsSystem().sceneMutator();
		sceneMutator.scene.removeModel(PLAY_MODEL_ID);
	}

	runner.uiSystem().removeEventAction<polymorph::sys::event::PointerDown>(UI_CLICK_ID);

	runner.graphicsSystem().actionQueue().pushAction
	(
		[](polymorph::sys::GraphicsSystemRunner& grRunner)
		{
			// TODO Something?
		}
	);
}

void MainMenuState::update(GameRunner& runner, TimeDuration dt)
{

}



}